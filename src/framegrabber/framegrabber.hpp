#pragma once

#include "imagesource.hpp"

#include "image.hpp"
#include "video_capture.hpp"

namespace soda {

class FrameGrabber
{
private:
    VideoCapture _capture;
    volatile bool _stopped;
    Image _frontBuffer;
    Image _backBuffer;
//    QReadWriteLock _lock;
    int _targetFps;

    void _switch_buffers();

protected:
    void run();

public:
    FrameGrabber(int fps = 10);
    ~FrameGrabber();
    bool open(int id);
    bool open(std::string& name);
    void close();
    bool is_open();
    void set_fps(int fps);
    void get_image(Image& dest);
    void stop();
};

} // namespace soda
