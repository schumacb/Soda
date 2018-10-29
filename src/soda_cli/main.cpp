#include "core/types.hpp"

#include <commandlineparser.hpp>

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "blobdetect/blobdetect.hpp"
#include "image.hpp"

using namespace std;
using namespace soda;

int main(int argc, char *argv[])
{
    CommandLineParser parser;
    auto& helpOption = parser.add_help_flag();
    parser.parse(argc, argv);

    Image input_image;
    input_image.read("source.jpg");

    if(input_image.is_empty())
    {
        cerr << "frame was empty!!!";
        return -1;
    }

    BlobDetecResult blob_detect_result;
    auto& threshold_result = blob_detect_result.threshold_result;

    int erosion_size = 3;
    int dilation_size = 3;

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

    BlobDetecSettings blobdetect_settings{
        255,
        channel,
        erosion_element,
        dilation_element,
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

    input_image.write("000-source.jpg");
    threshold_result.hue.write("010-hue.jpg");
    threshold_result.hue_threshold.write("011-hue-threshold.jpg");
    threshold_result.sat.write("021-sat.jpg");
    threshold_result.sat_threshold.write("021-sat-threshold.jpg");
    threshold_result.val.write("030-val.jpg");
    threshold_result.val_threshold.write("031-val-threshold.jpg");
    threshold_result.threshold.write("100-threshold.jpg");
    blob_detect_result.denoised_result.write("101-threshold-denoised.jpg");

    Image colored_threshold;
    blob_detect_result.denoised_result.convert_color(colored_threshold, ColorSpace::RGB);
    Image tmp;
    multiply(input_image, colored_threshold, tmp, 1.0/255.0);
    tmp.write("200-colored-threshold.jpg");
    return 0;
}
