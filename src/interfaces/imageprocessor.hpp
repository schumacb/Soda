#pragma once

#include "frame.hpp"
#include "blob.hpp"

#include <QThread>
#include <QWaitCondition>
#include <QMutex>
#include <QVector>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace soda {

class ImageProcessor : public QThread
{
    Q_OBJECT

protected:
    volatile bool _stopped;
    QWaitCondition _imageReady;
    QMutex _mutex;
public:
    ImageProcessor(QObject *parent)
        : QThread(parent), _stopped(false), _imageReady(), _mutex()
    {}
    ~ImageProcessor(){}

    virtual void stop() = 0;

    public slots:
        virtual void updateImage() = 0;

protected:
    void run();

private:
    virtual void processImage() = 0;

};

} // soda
