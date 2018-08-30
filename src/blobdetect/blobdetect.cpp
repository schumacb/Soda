#include "blobdetect.hpp"

#include <opencv2/calib3d/calib3d.hpp>

namespace soda
{

BlobDetect::BlobDetect(QObject *parent, ApplicationModel &model)
        : ImageProcessor(parent), _model(model), hsv(), hue(), sat(), val(),
          thrash(), hueThrash(), satThrash(), valThrash(), tmp(),
          erosionElement(), dilationElement(), contours(),
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
        dilation_type = erosion_type = cv::MORPH_ELLIPSE;

        erosionElement = cv::getStructuringElement( erosion_type,
                cv::Size( 2 * erosion_size + 1, 2 * erosion_size + 1 ),
                cv::Point( erosion_size, erosion_size ));
        dilationElement = cv::getStructuringElement( dilation_type,
                cv::Size( 2 * dilation_size + 1, 2 * dilation_size + 1 ),
                cv::Point( dilation_size, dilation_size ));

        Frame *frame = _model.requireFrame();
        _model.getImage(frame->img);

        frame->data.clear();

        for(int chanIdx = 0; chanIdx < channels->size() &&
                (*frame->img.size) > 0; ++chanIdx) {
                chan_ptr channel = channels->at(chanIdx);
                ChannelData data;
                data.chan = channel;

                int minHue = channel->minHue(),
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
                        int tmp = minHue;
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

                cv::cvtColor(frame->img, hsv, CV_RGB2HSV);

                cv::split(hsv, mv);
                hue = mv[0];
                sat = mv[1];
                val = mv[2];

                cv::threshold(hue, thrash, maxHue, 255, cv::THRESH_TOZERO_INV);
                cv::threshold(thrash, hueThrash, minHue, 255,
                        (invertHueThrash ? cv::THRESH_BINARY_INV : cv::THRESH_BINARY));

                cv::threshold(sat, thrash, maxSat, 255, cv::THRESH_TOZERO_INV);
                cv::threshold(thrash, satThrash, minSat, 255,
                        (invertSatThrash ? cv::THRESH_BINARY_INV : cv::THRESH_BINARY));

                cv::threshold(val, thrash, maxVal, 255, cv::THRESH_TOZERO_INV);
                cv::threshold(thrash, valThrash, minVal, 255,
                        (invertValThrash ? cv::THRESH_BINARY_INV : cv::THRESH_BINARY));

                cv::min(hueThrash, satThrash, thrash);
                cv::min(thrash, valThrash, thrash);

                // Apply the erosion operation to remove false positives from noise
                erode( thrash, thrash, erosionElement );

                // Apply the dilation operation to remove false negatives from noise
                dilate( thrash, thrash, dilationElement );

                // Convert graysacle image to rgb to be used by qt
                cv::cvtColor(thrash, tmp, CV_GRAY2RGB);
                tmp.copyTo(data.threshold);

                // Finds contours
                findContours(thrash,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);

                // Extract blob information
                int area = 0;
                int idx = -1;
                QVector<Blob> &blobs = data.blobs;
                for(int i=0; i<contours.size();++i) {

                        area = cv::contourArea(contours[i]);

                        if (area >= minArea) {
                                Blob blob;
                                blob.area = area;

                                // Calculates the bounding rect of the area contour
                                cv::Rect rect = boundingRect(contours[i]);

                                blob.left = rect.x;
                                blob.top = rect.y;
                                blob.right = rect.x + rect.width;
                                blob.bottom = rect.y + rect.height;
                                blobs.append(blob);
                        }
                }

                // sort blobs in ascending order
                qSort(blobs);

                // remove small blobs (requires blobs to be sorted ascending)
                while(blobs.size() > maxBlobs) {
                        blobs.remove(0);
                }

                frame->data.append(data);
        }
        _model.releaseFrame();
}

void BlobDetect::updateImage() {
        QMutexLocker locker(&_mutex);
        _imageReady.wakeOne();
}


}
