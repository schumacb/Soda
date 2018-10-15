#include "blobdetect.hpp"

namespace soda
{

BlobDetect::BlobDetect(BlobDetecSettings settings)
        : _settings(settings) { }

BlobDetect::~BlobDetect() { }

void BlobDetect::process(cv::InputArray inputImage, BlobDetecResult& result)
{
    if(inputImage.empty())
    {
        return;
    }

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
    cv::cvtColor(inputImage, hsv, cv::COLOR_RGB2HSV);
    auto& hue = result.hue;
    auto& sat = result.sat;
    auto& val = result.val;
    cv::split(hsv, result.hsvComponents);
    cv::Mat& thrash = result.thrash;
    cv::Mat& hue_thrash = result.hue_thrash;
    cv::Mat& sat_thrash = result.sat_thrash;
    cv::Mat& val_thrash = result.val_thrash;
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

    // Apply the erosion operation to remove false positives from noise
    cv::erode(thrash, thrash, _settings.erosion_element);

    // Apply the dilation operation to remove false negatives from noise
    cv::dilate(thrash, thrash, _settings.dilation_element);

    // Finds contours
    auto & contours = result.contours;
    cv::findContours(thrash, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

    // Convert graysacle image to rgb to be used by qt
    cv::cvtColor(thrash, thrash, cv::COLOR_GRAY2RGB);

    // Extract blob information
    unsigned int area = 0;
    auto& blobs = result.blobs;
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

    // sort blobs in ascending order
    std::sort(blobs.begin(), blobs.end());

    // remove small blobs (requires blobs to be sorted ascending)
    while(blobs.size() > _settings.maxBlobs)
    {
        blobs.erase(blobs.begin());
    }
}

}
