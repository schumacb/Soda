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
    BGR,
    Gray,
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
public:
    cv::Mat mat;
    cv::Mat components[3];
    ColorSpace color_space;

    class ConversionException : public std::exception
    {
    private:
        String _message;    
    public:
        ConversionException(const char* message) : _message(message) {}
        const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_USE_NOEXCEPT
        {
            return _message.c_str();
        }
    };
    Image() {}
    Image(cv::Mat mat, ColorSpace color_space) : mat(mat), color_space(color_space) {}
    Image(MorphShape shape, int size) : Image(shape, size, size) {}
    Image(MorphShape shape, int width, int height)
    {
        mat = cv::getStructuringElement(shape, cv::Size(width, height));
    }

    int width()
    {
        return mat.size[0];
    }

    int height()
    {
        return mat.size[1];
    }

    void read(const String& file_name)
    {
        mat = cv::imread(cv::String(file_name));
        color_space = ColorSpace::BGR;
    }

    bool write(const String& file_name)
    {
        return cv::imwrite(cv::String(file_name), mat);
    }

    void split()
    {
        cv::split(mat, components);
    }

    void merge()
    {
        cv::merge(components, 3, mat);
    }

    bool is_empty() const
    {
        mat.empty();
    }

    Image operator[](int index)
    {
        return Image(components[index], ColorSpace::Gray);
    }

    void threshold(Image& output_image, f64 value, f64 max_value, ThresholdType type) const
    {
        cv::threshold(mat, output_image.mat, value, max_value, type);
    }

    void convert_color(ColorSpace color_space)
    {
        convert_color(*this, color_space);
    }

    void convert_color(Image& destination, ColorSpace p_color_space) const
    {
        switch (color_space)
        {
        case BGR:
            convert_bgr_to(destination, p_color_space);
            break;
        case RGB:
            convert_rgb_to(destination, p_color_space);
            break;
        case HSV:
            convert_hsv_to(destination, p_color_space);
            break;
        default:
            throw new ConversionException("Unknown source color space");
        }
    }

    void find_contours(Vector<Vector<Point>>& contours)
    {
        cv::findContours(mat, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    }

    friend void erode(const Image& input, Image& destination, const Image& erosion_element)
    {
        cv::erode(input.mat, destination.mat, erosion_element.mat);
    }

    friend void dilate(const Image& input, Image& destination, const Image& dilation_element)
    {
        cv::dilate(input.mat, destination.mat, dilation_element.mat);
    }

    friend void min(const Image& a, const Image& b, Image& destination)
    {
        cv::min(a.mat, b.mat, destination.mat);
    }

    friend void multiply(const Image& a, const Image& b, Image& destination, f64 scale)
    {
        cv::multiply(a.mat, b.mat, destination.mat, scale);
    }

    operator const cv::Mat&() const
    {
        return mat;
    }

private:
    void convert_bgr_to(Image& destination, ColorSpace color_space) const
    {
        switch (color_space)
        {
        case HSV:
            cv::cvtColor(mat, destination.mat, CV_BGR2HSV);
        break;
        default:
            throw ConversionException("Unknown target color space");
        }
    }
    void convert_hsv_to(Image& destination, ColorSpace color_space) const
    {
        switch (color_space)
        {
        case RGB:
            cv::cvtColor(mat, destination.mat, CV_HSV2RGB);
        break;
        default:
            throw ConversionException("Unknown target color space");
        }
    }

    void convert_rgb_to(Image& destination, ColorSpace color_space) const
    {
        switch (color_space)
        {
        case HSV:
            cv::cvtColor(mat, destination.mat, CV_RGB2HSV);
        break;
        default:
            throw ConversionException("Unknown target color space");
        }
    }
};

} // namespace soda
