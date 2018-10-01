#pragma once

#include "imageprocessor.hpp"
#include "applicationmodel.hpp"

#include <image.hpp>

namespace soda {

class BlobDetect : public ImageProcessor
{
    Q_OBJECT
private:
    ApplicationModel& _model;
    Image erosion_element, dilation_element;

    Image hsv, hue, sat, val;
    Image thrash, hue_thrash, sat_thrash, val_thrash, tmp;

    std::vector<std::vector<Point>> contours;

    MorphShapes dilation_type,
        erosion_type;
    int dilation_size,
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
