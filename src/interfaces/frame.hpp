#pragma once

#include <opencv2/opencv.hpp>
#include <QVector>

#include "blob.hpp"
#include "channel.hpp"

namespace soda {

struct ChannelData {
    chan_ptr chan;
    cv::Mat threshold;
    QVector<Blob> blobs;
};

struct Frame
{
    cv::Mat img;
    QVector<ChannelData> data;
};

} // namespace soda
