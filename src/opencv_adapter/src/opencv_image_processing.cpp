#include "../include/image_processing.hpp"

#include "../include/types.hpp"

namespace soda {

int contour_area(std::vector<Point>& contour)
{
    cv::contourArea(contour);
}

}
