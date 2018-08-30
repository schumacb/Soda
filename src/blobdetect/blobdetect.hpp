#pragma once

#include "imageprocessor.hpp"
#include "applicationmodel.hpp"

namespace soda {

class BlobDetect : public ImageProcessor
{
    Q_OBJECT
private:
    ApplicationModel& _model;

    cv::Mat hsv, hue, sat, val;
    cv::Mat thrash, hueThrash, satThrash, valThrash, tmp;
    cv::Mat erosionElement, dilationElement;
    cv::Mat mv[3];
    std::vector<std::vector<cv::Point>> contours;

    int dilation_type,
        erosion_type,
        dilation_size,
        erosion_size;

public:
    BlobDetect(QObject *parent, ApplicationModel &model);
    ~BlobDetect();

    virtual void stop() = 0;

    public slots:
        virtual void updateImage() = 0;

protected:
    void run();

private:
    virtual void processImage() = 0;
};

} // namespace soda
