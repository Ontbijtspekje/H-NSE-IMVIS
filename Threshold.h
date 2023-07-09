#pragma once
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


using namespace cv;
using namespace std;

class Threshold {
private:
    Mat src, dst;
    int HEIGHT, WIDTH;

public:
    Threshold(cv::Mat& src, cv::Mat& dst);
    void process(int threshold);
};
