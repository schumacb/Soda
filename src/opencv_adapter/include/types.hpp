#pragma once

#include <opencv2/opencv.hpp>

namespace soda {
    typedef cv::Point Point;
    typedef cv::Size Size;
    typedef cv::MatSize MatrixSize;

enum ThresholdTypes {
    Binary = cv::THRESH_BINARY,
    BinaryInverse = cv::THRESH_BINARY_INV,
    Truncate = cv::THRESH_TRUNC,
    ToZero = cv::THRESH_TOZERO,
    ToZeroInverse = cv::THRESH_TOZERO_INV,
    Mask = cv::THRESH_MASK,
    Otsu = cv::THRESH_OTSU,
    Triangle = cv::THRESH_TRIANGLE
};

enum ContourRetrievalModes {
    External = CV_RETR_EXTERNAL,
    List = CV_RETR_LIST,
    CComp = CV_RETR_CCOMP,
    Tree = CV_RETR_TREE,
    FloodFill = CV_RETR_FLOODFILL
};

enum ContourApproximationMethods {
    Code = CV_CHAIN_CODE,
    None = CV_CHAIN_APPROX_NONE,
    Simple = CV_CHAIN_APPROX_SIMPLE,
    TC89_L1 = CV_CHAIN_APPROX_TC89_L1,
    TC89_KCOS = CV_CHAIN_APPROX_TC89_KCOS,
    LinkRuns = CV_LINK_RUNS
};

}
