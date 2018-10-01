#pragma once

#include "types.hpp"
#include "image_processing.hpp"

namespace soda {

    class Image
    {
    private:

    public:

        cv::Mat mat; // TODO: move to OpenCvImage

        bool is_empty();
        void show_in(std::string winname);
        MatrixSize get_size();
        void bgr_to_rgb(Image& out);
        void rgb_to_hsv(Image& out);
        void gray_to_rgb(Image& out);
        void split(Image& out1, Image& out2, Image& out3);
        void find_contours(std::vector<std::vector<Point>>& contours, ContourRetrievalModes mode, ContourApproximationMethods method);
        void copy_to(Image& out);
        void threshold(Image& out, double thresh, double maxval, ThresholdTypes type);
        static void min(const Image& a, const Image& b, Image& out);
        void erode(Image& out, const Image& erosionElement);
        void dilate(Image& out, const Image& dilationElement);
        static void get_structuring_element(Image& out, MorphShapes shape, int size);
    };
}
