#pragma once

#include <QThread>
#include <QReadWriteLock>
#include <opencv2/opencv.hpp>

#include "imagesource.hpp"

namespace soda {

class FrameGrabber : public QThread, public ImageSource
{
    Q_OBJECT

private:
    cv::VideoCapture _capture;
    volatile bool _stopped;
    cv::Mat _frontBuffer;
    cv::Mat _backBuffer;
    QReadWriteLock _lock;
    int _targetFps;

    void _switchBuffers();

protected:
    void run();

public:
    FrameGrabber(QObject *parent, int fps = 10);
    ~FrameGrabber();
    bool open(int id);
    bool open(QString name);
    void close();
    bool isOpened();
    void setFPS(int fps);
    void getImage(cv::Mat &dest);
    void stop();

    signals:
        void signal_imageReady(ImageSource &src);
};

} // namespace soda
