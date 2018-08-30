#include "framegrabber.hpp"
#include <sstream>
#include <iomanip>
#include <time.h>
#include <QDebug>
#include <QTime>

namespace soda {

FrameGrabber::FrameGrabber(QObject *parent, int fps)
    :QThread(parent), _capture(), _stopped(false), _frontBuffer(), _backBuffer(), _lock(), _targetFps(fps) { }

FrameGrabber::~FrameGrabber() { }

bool FrameGrabber::open(int id) {
    bool result = _capture.open(id);
    if (!result) qDebug() << "couldn't open device: " << id;
    return result;
}

bool FrameGrabber::open(QString name) {
    bool result = _capture.open(name.toStdString());
    if (!result) qDebug() << "couldn't open stream: " << name;
    return result;
}

void FrameGrabber::close()
{
    _capture.release();
}

bool FrameGrabber::isOpened() {
    return _capture.isOpened();
}

void FrameGrabber::setFPS(int fps) {
    _targetFps = fps;
}

void FrameGrabber::_switchBuffers() {
        _lock.lockForWrite();
        cvtColor(_backBuffer, _frontBuffer,CV_BGR2RGB);
        _lock.unlock();

        emit signal_imageReady(*this);
    }

void FrameGrabber::run() {
//    int imgCount = 0;
    int elapsed;
    int target = 1000/_targetFps;
    QTime time;
    time.start();
    while(!_stopped)
    {
        if(_capture.isOpened())
        {
            _capture >> _backBuffer;
            //std::ostringstream sstr;
            //sstr << std::setfill('0') << std::setw (10);
            //sstr << imgCount++;

            //std::string fileName = "f:\\tmp\\orig\\img" + sstr.str() + ".jpg";
            //cv::imwrite(fileName, _backBuffer);

            elapsed = time.elapsed();

            if (elapsed >= target) {
                _switchBuffers();
                time.start();
            }
        } else {
            msleep(1000);
        }
    }
}

void FrameGrabber::stop() {
    _stopped = true;
}

void FrameGrabber::getImage(cv::Mat &dest) {
    _lock.lockForRead();
    _frontBuffer.copyTo(dest);
    _lock.unlock();
}

}
