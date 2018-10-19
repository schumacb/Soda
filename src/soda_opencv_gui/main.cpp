#include <vector>

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

    cv::VideoCapture capture;
    if(!capture.open(0))
    {
        cout << "Could not open Camera!\n";
        return -1;
    }
    cv::Mat frame;
    BlobDetecResult blob_detect_result;
    auto& threshold_result = blob_detect_result.threshold_result;
    vector<NamedMat> window_names = {
        {"sourceImage", frame},
        {"hsv", threshold_result.hsv},
        {"hue", threshold_result.hue},
        {"hue-threshold", threshold_result.hue_threshold},
        {"sat", threshold_result.sat},
        {"sat-threshold", threshold_result.sat_threshold},
        {"val", threshold_result.val},
        {"val-threshold", threshold_result.val_threshold},
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
        {40,90},
        {75,255},
        {75,255}
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

    while(true)
    {
        capture >> frame;
        if(!frame.empty())
        {
            blobDetect.process(frame, blob_detect_result);
            show_images(window_names);
        }
        else
        {
            cout << "frame was empty!!!";
        }
        auto key = cv::waitKey(1);
        if (key == 27) break;
    }
    return 0;
}
