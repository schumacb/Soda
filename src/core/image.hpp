#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

#include "types.hpp"

namespace soda
{

typedef cv::Point Point;

enum MorphShape
{
    Rectangle = cv::MORPH_RECT,
    Cross = cv::MORPH_CROSS,
    Ellipse = cv::MORPH_ELLIPSE
};

enum ColorSpace
{
    RGB,
    HSV
};

enum ThresholdType
{
    Binary = cv::THRESH_BINARY,
    BinaryInverse = cv::THRESH_BINARY_INV,
    Truncate = cv::THRESH_TRUNC,
    ToZero = cv::THRESH_TOZERO,
    ToZeroInverse = cv::THRESH_TOZERO_INV,
    Mask = cv::THRESH_MASK,
    Otsu = cv::THRESH_OTSU,
    Triangle = cv::THRESH_TRIANGLE,
};

class Image
{
private:
    cv::Mat _mat;
    cv::Mat _components[3];
    ColorSpace _color_space;


public:
    class ConversionException
    {
    private:
        String _message;
    public:
        ConversionException(const char* message) : _message(message) {}
    };
    Image() {}
    Image(cv::Mat mat) : _mat(mat) {}
    Image(MorphShape shape, int size) : Image(shape, size, size) {}
    Image(MorphShape shape, int width, int height)
    {
        _mat = cv::getStructuringElement(shape, cv::Size(width, height));
    }

    void read(const String& file_name)
    {
        _mat = cv::imread(cv::String(file_name));
    }

    bool write(const String& file_name)
    {
        return cv::imwrite(cv::String(file_name), _mat);
    }

    void split()
    {
        cv::split(_mat, _components);
    }

    bool is_empty() const
    {
        _mat.empty();
    }

    Image operator[](int index)
    {
        return Image(_components[index]);
    }

    void threshold(Image& output_image, f64 value, f64 max_value, ThresholdType type) const
    {
        cv::threshold(_mat, output_image._mat, value, max_value, type);
    }

    void convert_color(ColorSpace color_space)
    {
        convert_color(*this, color_space);
    }

    void convert_color(Image& destination, ColorSpace color_space) const
    {
        switch (_color_space)
        {
        case RGB:
            convert_rgb_to(destination, color_space);
            break;
        default:
            throw new ConversionException("Unknown source color space");
        }
    }

    void find_contours(Vector<Vector<Point>>& contours)
    {
        cv::findContours(_mat, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    }

    friend void erode(const Image& input, Image& destination, const Image& erosion_element)
    {
        cv::erode(input._mat, destination._mat, erosion_element._mat);
    }

    friend void dilate(const Image& input, Image& destination, const Image& dilation_element)
    {
        cv::dilate(input._mat, destination._mat, dilation_element._mat);
    }

    friend void min(const Image& a, const Image& b, Image& destination)
    {
        cv::min(a._mat, b._mat, destination._mat);
    }

    friend void multiply(const Image& a, const Image& b, Image& destination, f64 scale)
    {
        cv::multiply(a._mat, b._mat, destination._mat, scale);
    }

    operator const cv::Mat&() const
    {
        return _mat;
    }

private:
    void convert_rgb_to(Image& destination, ColorSpace color_space) const
    {
        switch (color_space)
        {
        case HSV:
            cv::cvtColor(_mat, destination._mat, CV_RGB2HSV);
        break;
        default:
            throw new ConversionException("Unknown target color space");
        }
    }
};

} // namespace soda
