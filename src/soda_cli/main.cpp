#include <vector>

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "blobdetect/blobdetect.hpp"

using namespace std;
using namespace soda;

int main(int argc, char **argv) {

    const cv::String keys =
        "{help h usage ? |      | print this message   }"
        "{@source        |      | image to process     }"
        "{path           |.     | path to file         }"
        "{fps            | -1.0 | fps for output video }"
        ;
    cv::CommandLineParser parser(argc, argv, keys);
    if(!parser.check())
    {
        parser.printErrors();
        return -1;
    }

    if(parser.has("help") || parser.has("h") || parser.has("usage") || parser.has("?"))
    {
        parser.printMessage();
    }

    cv::Mat input_image;

    if(parser.has("@source"))
    {
        auto file_name = parser.get<cv::String>("@source");
        input_image = cv::imread(file_name);
    }
    else {
        cerr << "Missing required parameter source!";
        return -2;
    }

    if(input_image.empty())
    {
        cerr << "frame was empty!!!";
        return -3;
    }

    BlobDetecResult blob_detect_result;
    auto& threshold_result = blob_detect_result.threshold_result;

    int erosion_size = 3;
    int dilation_size = 3;

    auto erosion_element = cv::getStructuringElement(cv::MORPH_ELLIPSE,
                                cv::Size( 2 * erosion_size + 1, 2 * erosion_size + 1 ));
    auto dilation_element = cv::getStructuringElement(cv::MORPH_ELLIPSE,
                                cv::Size( 2 * dilation_size + 1, 2 * dilation_size + 1 ));

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
        erosion_element,
        dilation_element,
        channel,
        min_area,
        max_blobs
    };

    BlobDetect blobDetect(blobdetect_settings);

    f64 min = 105;
    f64 max = 135;

    channel.hue.min = min;
    channel.hue.max = max;
    blobDetect.process(input_image, blob_detect_result);

    cout << "hue: [" << min << ", " << max << "]\nblobs: ";
    for(auto blob : blob_detect_result.blobs)
    {
        cout << blob.area << " ";
    }
    cout << "\n";

    {
        imwrite( "000-source.jpg", input_image );
        imwrite( "010-hue.jpg", threshold_result.hue );
        imwrite( "011-hue-threshold.jpg", threshold_result.hue_threshold );
        imwrite( "021-sat.jpg", threshold_result.sat );
        imwrite( "021-sat-threshold.jpg", threshold_result.sat_threshold );
        imwrite( "030-val.jpg", threshold_result.val );
        imwrite( "031-val-threshold.jpg", threshold_result.val_threshold );
        imwrite( "100-threshold.jpg", threshold_result.threshold );
        imwrite( "101-threshold-denoised.jpg", blob_detect_result.denoised_result );
    }

    {
        cv::Mat colored_threshold;
        cv::cvtColor(blob_detect_result.denoised_result, colored_threshold, CV_GRAY2RGB);
        cv::Mat tmp;
        cv::multiply(input_image, colored_threshold, tmp, 1.0/255.0);
        imwrite("200-colored-threshold.jpg", tmp);
    }

    {
        auto& hsv = threshold_result.hsv;
        auto& hue = threshold_result.hue;
        auto hue_size = hue.size();
        auto hue_type = hue.type();
        cv::Mat hsv_components[3];
        auto hsv_channels = static_cast<size_t>(hsv.channels());
        hsv_components[0] = hue;
        auto scalar = cv::Scalar(255 * 0.75);
        {
            cv::Mat colored_hue;
            hsv_components[0] = hue;
            hsv_components[1] = cv::Mat(hue_size, hue_type, scalar);
            hsv_components[2] = cv::Mat(hue_size, hue_type, scalar);

            cv::merge(hsv_components, hsv_channels, colored_hue);
            cv::cvtColor(colored_hue, colored_hue, CV_HSV2RGB);
            imwrite("210-colored-hue.jpg", colored_hue);
        }
    }
    return 0;
}
