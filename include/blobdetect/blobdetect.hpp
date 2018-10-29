#pragma once

#include "core/types.hpp"

#include "image.hpp"

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
    f64 channel_range_max_value;
    Channel& channel;
    Image erosion_element,
          dilation_element;
    u32 minArea;
    u32 maxBlobs;
};

struct ThresholdResult
{
    Image hsv;
    Image hue = hsv[0];
    Image sat = hsv[1];
    Image val = hsv[2];
    Image threshold;
    Image hue_threshold;
    Image sat_threshold;
    Image val_threshold;
};

struct BlobDetecResult
{
    ThresholdResult threshold_result;
    Image denoised_result;
    Vector<Vector<Point>> contours;
    Vector<Blob> blobs;
};

class BlobDetect
{
    BlobDetecSettings& _settings;
public:
    BlobDetect(BlobDetecSettings& settings);
    ~BlobDetect();
    void process(Image input_image, BlobDetecResult& result);
    void calculate_threshold(Image &input_image, ThresholdResult &result);
    void denoise(Image imput_image, Image result);
    void extract_blob_information(Vector<Vector<Point> > contours, Vector<Blob> blobs);
    void remove_small_blobs(Vector<Blob>& blobs);
    void threshold(const Image& input_image, Image& output_image, ChannelRange range, bool invert_binary);
};

} // namespace soda
