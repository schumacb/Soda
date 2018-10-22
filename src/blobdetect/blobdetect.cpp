#include "blobdetect.hpp"

namespace soda
{

BlobDetect::BlobDetect(BlobDetecSettings &settings)
        : _settings(settings) { }

BlobDetect::~BlobDetect() { }

void BlobDetect::calculate_threshold(cv::InputArray input_image, ThresholdResult& result)
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
    cv::cvtColor(input_image, hsv, cv::COLOR_RGB2HSV);
    auto& hue = result.hue;
    auto& sat = result.sat;
    auto& val = result.val;
    cv::split(hsv, result.hsv_components);

    cv::Mat& thrash = result.threshold;
    cv::Mat& hue_thrash = result.hue_threshold;
    cv::Mat& sat_thrash = result.sat_threshold;
    cv::Mat& val_thrash = result.val_threshold;
    auto max_range = 255;
    cv::threshold(hue, thrash, hue_range.max, max_range, cv::THRESH_TOZERO_INV);
    cv::threshold(thrash ,hue_thrash, hue_range.min, max_range,
                    (invertHueThrash ? cv::THRESH_BINARY_INV : cv::THRESH_BINARY));

    cv::threshold(sat, thrash, satuartion_range.max, max_range, cv::THRESH_TOZERO_INV);
    cv::threshold(thrash, sat_thrash, satuartion_range.min, max_range,
                    (invertSatThrash ? cv::THRESH_BINARY_INV : cv::THRESH_BINARY));

    cv::threshold(val, thrash, value_range.max, max_range, cv::THRESH_TOZERO_INV);
    cv::threshold(thrash, val_thrash, value_range.min, max_range,
                    (invertValThrash ? cv::THRESH_BINARY_INV : cv::THRESH_BINARY));

    cv::min(hue_thrash, sat_thrash, thrash);
    cv::min(thrash, val_thrash, thrash);
}

void BlobDetect::denoise(cv::InputArray imput_image, cv::OutputArray result)
{
    cv::erode(imput_image, result, _settings.erosion_element);
    cv::dilate(result, result, _settings.dilation_element);
    cv::dilate(result, result, _settings.dilation_element);
    cv::erode(result, result, _settings.erosion_element);
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

void BlobDetect::remove_small_blobs(std::vector<Blob>& blobs)
{
    std::sort(blobs.begin(), blobs.end());

    // remove small blobs (requires blobs to be sorted ascending)
    while(blobs.size() > _settings.maxBlobs)
    {
        blobs.erase(blobs.begin());
    }
}

void BlobDetect::process(cv::InputArray inputImage, BlobDetecResult& result)
{
    if(inputImage.empty())
    {
        return;
    }
    auto & thrash = result.threshold_result.threshold;
    calculate_threshold(inputImage, result.threshold_result);
    denoise(result.threshold_result.threshold, result.denoised_result);

    // Finds contours
    auto & contours = result.contours;
    cv::findContours(thrash, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

    // Extract blob information
    extract_blob_information(contours, result.blobs);
    remove_small_blobs(result.blobs);
}

}
