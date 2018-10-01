#include "../include/video_capture.hpp"


namespace soda {

bool VideoCapture::open(int index)
{
    return captureComponent.open(index);
}

bool VideoCapture::open(std::string& filename)
{
    return captureComponent.open(filename);
}

bool VideoCapture::is_open()
{
    return captureComponent.isOpened();
}

void VideoCapture::release()
{
    captureComponent.release();
}

double VideoCapture::get_fps()
{
    return captureComponent.get(cv::CAP_PROP_FPS);
}

void VideoCapture::read(Image& destination)
{
    captureComponent.read(destination.mat);
}

}
