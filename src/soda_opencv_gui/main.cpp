#include <vector>

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "blobdetect/blobdetect.hpp"

using namespace std;
using namespace soda;

struct NamedMat {
    cv::String name;
    const cv::Mat& mat;
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
    vector<NamedMat> window_names;
    window_names.push_back(NamedMat{"sourceImage", frame});
    window_names.push_back(NamedMat{"hsv", threshold_result.hsv});
    window_names.push_back(NamedMat{"hue", threshold_result.hue});
    window_names.push_back(NamedMat{"hue-threshold", threshold_result.hue_threshold});
    window_names.push_back(NamedMat{"sat", threshold_result.sat});
    window_names.push_back(NamedMat{"sat-threshold", threshold_result.sat_threshold});
    window_names.push_back(NamedMat{"val", threshold_result.val});
    window_names.push_back(NamedMat{"val-threshold", threshold_result.val_threshold});
    window_names.push_back(NamedMat{"threshold", threshold_result.threshold});

    create_windows(window_names);
    int erosion_size = 2;
    int dilation_size = 2;

    auto erosion_element = Image(MorphShape::Ellipse, erosion_size);
    auto dilation_element = Image(MorphShape::Ellipse, dilation_size);

    Channel channel
    {
        {90,200},
        {20,255},
        {20,255}
    };
    u32 min_area = 10;
    u32 max_blobs = 10;
    BlobDetecSettings blobdetect_settings
    {
        255,
        channel,
        erosion_element,
        dilation_element,
        min_area,
        max_blobs
    };
    BlobDetect blobDetect(blobdetect_settings);

    while(true)
    {
        capture >> frame;
        if(!frame.empty())
        {
            blobDetect.process(Image(frame, ColorSpace::RGB), blob_detect_result);
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
