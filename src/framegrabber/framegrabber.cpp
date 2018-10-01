#include "framegrabber.hpp"
//#include <sstream>
//#include <iomanip>
//#include <time.h>
//#include <QDebug>
//#include <QTime>

namespace soda {

FrameGrabber::FrameGrabber(int fps)
//    :QThread(parent)//, _capture(), _stopped(false), _frontBuffer(), _backBuffer(), _lock(), _targetFps(fps)
{
}

FrameGrabber::~FrameGrabber() { }

bool FrameGrabber::open(int id) {
//    bool result = _capture.open(id);
//    if (!result) qDebug() << "couldn't open device: " << id;
//    return result;
    return false;
}

bool FrameGrabber::open(std::string& name) {
//    bool result = _capture.open(name);
//    if (!result) qDebug() << "couldn't open stream: " << QString(name.c_str());
//    return result;
    return false;
}

void FrameGrabber::close()
{
//    _capture.release();
}

bool FrameGrabber::is_open() {
//    return _capture.is_open();
    return false;
}

void FrameGrabber::set_fps(int fps) {
//    _targetFps = fps;
}

void FrameGrabber::_switch_buffers() {
//        _lock.lockForWrite();
//        _backBuffer.bgr_to_rgb(_frontBuffer);
//        _lock.unlock();

//        emit signal_imageReady(*this);
    }

void FrameGrabber::run() {
////    int imgCount = 0;
//    int elapsed;
//    qDebug() << "FPS: " << _capture.get_fps();
//    int target = 1000/_targetFps;
//    QTime time;
//    time.start();
//    while(!_stopped)
//    {
//        if(_capture.is_open())
//        {
//            _capture.read(_backBuffer);
//            //std::ostringstream sstr;
//            //sstr << std::setfill('0') << std::setw (10);
//            //sstr << imgCount++;

//            //std::string fileName = "f:\\tmp\\orig\\img" + sstr.str() + ".jpg";
//            //cv::imwrite(fileName, _backBuffer);

//            elapsed = time.elapsed();

//            if (elapsed >= target) {
//                _switch_buffers();
//                time.start();
//            }
//        } else {
//            msleep(1000);
//        }
//    }
}

void FrameGrabber::stop() {
//    _stopped = true;
}

void FrameGrabber::get_image(Image &dest) {
//    _lock.lockForRead();
//    _frontBuffer.copy_to(dest);
//    _lock.unlock();
}

}
