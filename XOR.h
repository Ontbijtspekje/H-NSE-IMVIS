#pragma once
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;


class XOR {
private:
    Mat src1, src2, dst;
    int HEIGHT, WIDTH;

public:
    XOR(cv::Mat& src1, cv::Mat& src2, cv::Mat& dst);
    void process();
};
