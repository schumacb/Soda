#pragma once

#include "core/image.hpp"
#include "core/types.hpp"
#include "opencv2/opencv.hpp"

namespace soda {

struct Blob{
    u32 area;
    i32 top;
    i32 left;
    i32 right;
    i32 bottom;

    friend bool operator<(const Blob& left, const Blob& right)
    {
        return left.area < right.area;
    }
};

struct ChannelRange{
    f64 min;
    f64 max;
public:
    void swap()
    {
        auto tmp = min;
        min = max;
        max = tmp;
    }
};

struct Channel {
    ChannelRange hue;
    ChannelRange value;
    ChannelRange saturation;
};

struct BlobDetecSettings
{
    cv::Mat erosion_element,
            dilation_element;
    Channel channel;
    u32 minArea;
    u32 maxBlobs;
};

struct BlobDetecResult{
    cv::Mat hsv;
    cv::Mat hsvComponents[3];
    cv::Mat& hue = hsvComponents[0];
    cv::Mat& sat = hsvComponents[1];
    cv::Mat& val = hsvComponents[2];
    cv::Mat thrash, hue_thrash, sat_thrash, val_thrash;
    std::vector<std::vector<cv::Point>> contours;
    std::vector<Blob> blobs;
};

class BlobDetect
{
    BlobDetecSettings _settings;
public:
    BlobDetect(BlobDetecSettings settings);
    ~BlobDetect();
    void process(cv::InputArray image, BlobDetecResult& result);
};

} // namespace soda
