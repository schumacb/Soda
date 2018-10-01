#include "../include/image.hpp"

namespace soda
{

bool Image::is_empty()
{
    return mat.empty();
}

void Image::show_in(std::string winname) {
    cv::imshow(winname, mat);
}


MatrixSize Image::get_size() {
    return mat.size;
}

void Image::bgr_to_rgb(Image& out)
{
    cv::cvtColor(mat, out.mat, CV_BGR2RGB);
}

void Image::rgb_to_hsv(Image& out)
{
    cv::cvtColor(mat, out.mat, CV_RGB2HSV);
}

void Image::gray_to_rgb(Image& out)
{
    cv::cvtColor(mat, out.mat, CV_GRAY2RGB);
}

void Image::split(Image& out1, Image& out2, Image& out3)
{
    cv::Mat mv[3];
    cv::split(mat, mv);
    out1.mat = mv[0];
    out2.mat = mv[1];
    out3.mat = mv[2];
}

void Image::find_contours(std::vector<std::vector<Point>>& contours, ContourRetrievalModes mode, ContourApproximationMethods method) {

    cv::findContours(mat, contours, mode, method);
}

void Image::copy_to(Image& out)
{
    mat.copyTo(out.mat);
}

void Image::threshold(Image& out, double thresh, double maxval, ThresholdTypes type)
{
    cv::threshold(mat, out.mat, thresh, maxval, type);
}

void Image::min(const Image& a, const Image& b, Image& out)
{
    cv::min(a.mat, b.mat, out.mat);
}

void Image::erode(Image& out, const Image& erosionElement)
{
    cv::erode(mat, out.mat, erosionElement.mat);
}

void Image::dilate(Image& out, const Image& dilationElement)
{
    cv::dilate(mat, out.mat, dilationElement.mat);
}

void Image::get_structuring_element(Image& out, MorphShapes shape, int size)
{
    out.mat = cv::getStructuringElement(shape,
                                        Size( 2 * size + 1, 2 * size + 1 ),
                                        cv::Point( size, size ));
}

}
