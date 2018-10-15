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
    cv::Mat& mat;
};

void create_windows(vector<NamedMat> list) {
    for (auto mat : list) {
        cv::namedWindow(mat.name);
    }
}

void show_images(vector<NamedMat> list)
{
    for(auto namedMat : list)
    {
        auto mat = namedMat.mat;
        auto name = namedMat.name;
        if(!mat.empty())
        {
            cv::imshow(name, mat);
        }
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
    auto& threshold_result = blob_detect_result.threshold_result;
    vector<NamedMat> window_names = {
        {"sourceImage", frame},
        {"hsv", threshold_result.hsv},
        {"hue", threshold_result.hue_threshold},
        {"sat", threshold_result.sat_threshold},
        {"val", threshold_result.val_threshold},
        {"threshold", threshold_result.threshold}
    };
    create_windows(window_names);
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
    u32 min_area = 10;
    u32 max_blobs = 10;
    BlobDetecSettings blobdetect_settings
    {
        erosion_element,
        dilation_element,
        channel,
        min_area,
        max_blobs
    };
    BlobDetect blobDetect(blobdetect_settings);

    while(!app.closingDown())
    {
        capture >> frame;
        if(!frame.empty())
        {
            blobDetect.process(frame, blob_detect_result);
            show_images(window_names);
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
