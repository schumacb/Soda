#pragma once

#include <opencv2/imgproc.hpp>

#include "types.hpp"

namespace soda {

typedef cv::MorphTypes MorphTypes;
typedef cv::MorphShapes MorphShapes;

// TODO: move to image processing
int contour_area(std::vector<Point>& contour);

}
