#include "blobdetect.hpp"

namespace soda
{

BlobDetect::BlobDetect(BlobDetecSettings &settings)
        : _settings(settings) { }

BlobDetect::~BlobDetect() { }

void BlobDetect::threshold(const Image& input_image, Image& output_image, ChannelRange range, bool invert_binary)
{
    auto max_value = _settings.channel_range_max_value;
    input_image.threshold(output_image, range.max, max_value, ThresholdType::ToZeroInverse);
    output_image.threshold(output_image, range.min, max_value,
                           (invert_binary ? ThresholdType::BinaryInverse : ThresholdType::Binary));
}

void BlobDetect::calculate_threshold(Image& input_image, ThresholdResult& result)
{
    Channel& channel = _settings.channel;
    ChannelRange& hue_range = channel.hue;
    ChannelRange& value_range = channel.value;
    ChannelRange& satuartion_range = channel.saturation;

    bool invertHueThrash = false,
            invertSatThrash = false,
            invertValThrash = false;

    if (hue_range.min > hue_range.max) {
        hue_range.swap();
        invertHueThrash = true;
    }

    if (satuartion_range.min > satuartion_range.max) {
            satuartion_range.swap();
            invertSatThrash = true;
    }

    if (value_range.min > value_range.max) {
            value_range.swap();
            invertValThrash = true;
    }

    auto& hsv = result.hsv;
    input_image.convert_color(hsv, ColorSpace::HSV);
    auto& hue = result.hue;
    auto& sat = result.sat;
    auto& val = result.val;

    hsv.split();

    auto& thrash = result.threshold;
    auto& hue_thrash = result.hue_threshold;
    auto& sat_thrash = result.sat_threshold;
    auto& val_thrash = result.val_threshold;

    threshold(hue, hue_thrash, hue_range, invertHueThrash);
    threshold(sat, sat_thrash, satuartion_range, invertSatThrash);
    threshold(val, val_thrash, value_range, invertValThrash);

    min(hue_thrash, sat_thrash, thrash);
    min(thrash, val_thrash, thrash);
}

void BlobDetect::denoise(Image imput_image, Image result)
{
    erode(imput_image, result, _settings.erosion_element);
    dilate(result, result, _settings.dilation_element);
    dilate(result, result, _settings.dilation_element);
    erode(result, result, _settings.erosion_element);
}

void BlobDetect::extract_blob_information(std::vector<std::vector<cv::Point>> contours, std::vector<Blob> blobs)
{
    unsigned int area = 0;
    for(size_t i=0; i<contours.size(); ++i) {
        area = static_cast<unsigned int>(cv::contourArea(contours[i]));
        if (area >= _settings.minArea) {
                Blob blob;
                blob.area = area;

                // Calculates the bounding rect of the area contour
                cv::Rect rect = boundingRect(contours[i]);

                blob.left = rect.x;
                blob.top = rect.y;
                blob.right = rect.x + rect.width;
                blob.bottom = rect.y + rect.height;
                blobs.push_back(blob);
         }
    }
}

void BlobDetect::remove_small_blobs(Vector<Blob> &blobs)
{
    std::sort(blobs.begin(), blobs.end());

    // remove small blobs (requires blobs to be sorted ascending)
    while(blobs.size() > _settings.maxBlobs)
    {
        blobs.erase(blobs.begin());
    }
}

void BlobDetect::process(Image input_image, BlobDetecResult& result)
{
    if(input_image.is_empty())
    {
        return;
    }
    auto & thrash = result.threshold_result.threshold;
    calculate_threshold(input_image, result.threshold_result);
    denoise(result.threshold_result.threshold, result.denoised_result);

    // Finds contours
    auto & contours = result.contours;
    thrash.find_contours(contours);

    // Extract blob information
    extract_blob_information(contours, result.blobs);
    remove_small_blobs(result.blobs);
}

}
