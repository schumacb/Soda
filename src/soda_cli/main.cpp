#include <vector>

#include <QCoreApplication>
#include <QDebug>

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "blobdetect/blobdetect.hpp"

using namespace std;
using namespace soda;

struct NamedMat {
    cv::String name;
    cv::Mat mat;
};

void create_windows(vector<NamedMat> list) {
    for (auto mat : list) {
        cv::namedWindow(mat.name);
    }
}

void show_images(vector<NamedMat> list)
{
    for(auto mat : list)
    {
        cv::imshow(mat.name, mat.mat);
    }
}



int main(int argc, char **argv) {

    QCoreApplication app(argc, argv);

    app.addLibraryPath(QCoreApplication::applicationDirPath() + "/../lib");

    cv::VideoCapture capture;
    if(!capture.open(0))
    {
        qDebug() << "Could not open Camera!";
        return -1;
    }

    qDebug() << "fps: " << capture.get(cv::CAP_PROP_FPS);
    qDebug() << "format: " << capture.get(cv::CAP_PROP_FORMAT);
    cv::Mat frame;
    BlobDetecResult blob_detect_result;
    vector<NamedMat> window_names ={{"sourceImage", frame}};
    create_windows(window_names);
    vector<cv::Mat&> images = {frame,
                blob_detect_result.hsv,
                blob_detect_result.hue_thrash,
                blob_detect_result.sat_thrash,
                blob_detect_result.val_thrash,
                blob_detect_result.thrash };
    int erosion_size = 2;
    int dilation_size = 2;
    auto erosion_element = cv::getStructuringElement(cv::MORPH_ELLIPSE,
                                cv::Size( 2 * erosion_size + 1, 2 * erosion_size + 1 ));
    auto dilation_element = cv::getStructuringElement(cv::MORPH_ELLIPSE,
                                cv::Size( 2 * dilation_size + 1, 2 * dilation_size + 1 ));
    Channel channel
    {
        {0,255},
        {50,255},
        {50,255}
    };
    BlobDetecSettings blobdetect_settings
    {
        erosion_element,
        dilation_element,
        channel
    };

    BlobDetect blobDetect(blobdetect_settings);



    while(!app.closingDown())
    {

        capture >> frame;
        if(!frame.empty())
        {
            show_images(window_names);
            auto result = blobDetect.process(frame);
            cv::waitKey(1);
        }
        else
        {
            qDebug() << "frame was empty!!!";
        }
        app.processEvents();
    }

    return 0;
}
