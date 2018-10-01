#include "blobdetect.hpp"

#include <types.hpp>

namespace soda
{

BlobDetect::BlobDetect(QObject *parent, ApplicationModel &model)
        : ImageProcessor(parent), _model(model), hsv(), hue(), sat(), val(),
          thrash(), hue_thrash(), sat_thrash(), val_thrash(), tmp(),
          erosion_element(), dilation_element(), contours(),
          dilation_type(), erosion_type(), dilation_size(), erosion_size()
{
}

BlobDetect::~BlobDetect() {
}

void BlobDetect::run() {
        while (!_stopped) {
                QMutexLocker locker(&_mutex);
                processImage();
                _imageReady.wait(&_mutex);

        }
}

void BlobDetect::stop() {
        QMutexLocker locker(&_mutex);
        _stopped = true;
        _imageReady.wakeOne();
}

void BlobDetect::processImage() {
        const QVector<chan_ptr> *channels = _model.getChannels();

        erosion_size= 2;
        dilation_size = 3;
        dilation_type = erosion_type = MorphShapes::MORPH_ELLIPSE;

        Image::get_structuring_element(erosion_element, erosion_type, dilation_size);
        Image::get_structuring_element(dilation_element, dilation_type, dilation_size);

        Frame *frame = _model.requireFrame();
        _model.getImage(frame->img);

        frame->data.clear();

        for(int chanIdx = 0; chanIdx < channels->size() &&
                (*frame->img.get_size()) > 0; ++chanIdx) {
                chan_ptr channel = channels->at(chanIdx);
                ChannelData data;
                data.chan = channel;

                unsigned int minHue = channel->minHue(),
                        maxHue = channel->maxHue(),
                        minSat = channel->minSat(),
                        maxSat = channel->maxSat(),
                        minVal = channel->minVal(),
                        maxVal = channel->maxVal(),
                        minArea = channel->minArea(),
                        maxBlobs = channel->maxBlobs();

                bool invertHueThrash = false,
                        invertSatThrash = false,
                        invertValThrash = false;

                if (minHue > maxHue) {
                        unsigned int tmp = minHue;
                        minHue = maxHue;
                        maxHue = tmp;
                        invertHueThrash = true;
                }

                if (minSat > maxSat) {
                        int tmp = minSat;
                        minSat = maxSat;
                        maxSat = tmp;
                        invertSatThrash = true;
                }

                if (minVal > maxVal) {
                        int tmp = minVal;
                        minVal = maxVal;
                        maxVal = tmp;
                        invertValThrash = true;
                }

                frame->img.rgb_to_hsv(hsv);

                hsv.split(hue, sat, val);

                hue.threshold(thrash, maxHue, 255, ThresholdTypes::ToZeroInverse);
                thrash.threshold(hue_thrash, minHue, 255,
                        (invertHueThrash ? ThresholdTypes::BinaryInverse: ThresholdTypes::Binary));

                sat.threshold(thrash, maxSat, 255, ThresholdTypes::ToZeroInverse);
                thrash.threshold(sat_thrash, minSat, 255,
                        (invertSatThrash ? ThresholdTypes::BinaryInverse : ThresholdTypes::Binary));

                val.threshold(thrash, maxVal, 255, ThresholdTypes::ToZeroInverse);
                thrash.threshold(val_thrash, minVal, 255,
                        (invertValThrash ? ThresholdTypes::BinaryInverse: ThresholdTypes::Binary));

                Image::min(hue_thrash, sat_thrash, thrash);
                Image::min(thrash, val_thrash, thrash);

                // Apply the erosion operation to remove false positives from noise
                thrash.erode(thrash, erosion_element);

                // Apply the dilation operation to remove false negatives from noise
                thrash.dilate(thrash, dilation_element );

                // Convert graysacle image to rgb to be used by qt
                thrash.gray_to_rgb(tmp);
                tmp.copy_to(data.threshold);

                // Finds contours
                thrash.find_contours(contours, ContourRetrievalModes::External, ContourApproximationMethods::None);

                // Extract blob information
                unsigned int area = 0;
                std::vector<Blob> &blobs = data.blobs;
                for(size_t i=0; i<contours.size(); ++i) {

                        area = static_cast<unsigned int>(contour_area(contours[i]));

                        if (area >= minArea) {
                                Blob blob;
                                blob.area = area;

                                // Calculates the bounding rect of the area contour
                                cv::Rect rect = boundingRect(contours[i]);

                                blob.left = rect.x;
                                blob.top = rect.y;
                                blob.right = rect.x + rect.width;
                                blob.bottom = rect.y + rect.height;
                                blobs.push_back(blob);
                        }
                }

                // sort blobs in ascending order
                qSort(blobs);

                // remove small blobs (requires blobs to be sorted ascending)
                while(blobs.size() > maxBlobs) {
                    blobs.erase(blobs.begin());
                }

                frame->data.push_back(data);
        }
        _model.releaseFrame();
}

void BlobDetect::updateImage() {
        QMutexLocker locker(&_mutex);
        _imageReady.wakeOne();
}


}
