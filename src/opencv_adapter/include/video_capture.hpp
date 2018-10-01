#pragma once

#include <opencv2/videoio.hpp>

#include "image.hpp"

namespace soda {

class VideoCapture
{
private:
    cv::VideoCapture captureComponent;
public:
    bool open(int index);
    bool open(std::string& filename);
    bool is_open();
    void release();
    double get_fps();
    void read(Image& destination);
};

}
