#pragma once

#include "core/image.hpp"
#include "core/types.hpp"
#include "opencv2/opencv.hpp"

namespace soda {

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
};

struct BlobDetecResult{
    cv::Mat hsv;
    cv::Mat hsvComponents[3];
    cv::Mat& hue = hsvComponents[0];
    cv::Mat& sat = hsvComponents[1];
    cv::Mat& val = hsvComponents[2];
    cv::Mat thrash, hue_thrash, sat_thrash, val_thrash;
    //    std::vector<std::vector<Point>> contours;
};

class BlobDetect
{
    BlobDetecSettings _settings;
public:
    BlobDetect(BlobDetecSettings settings);
    ~BlobDetect();
    BlobDetecResult process(cv::InputArray image);
};

} // namespace soda
