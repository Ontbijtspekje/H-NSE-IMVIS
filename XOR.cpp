#include "XOR.h"

using namespace cv;
using namespace std;

XOR::XOR(cv::Mat& src1, cv::Mat& src2, cv::Mat& dst) {
    this->src1 = src1;
    this->src2 = src2;
    this->dst = dst;
}

/*
void XOR::process() {
    cv::bitwise_xor(src1, src2, dst);
}
*/

void XOR::process() {
    int HEIGHT = src1.rows;
    int WIDTH = src1.cols;

    for (int h = 0; h < HEIGHT; h++) {
        for (int w = 0; w < WIDTH; w++) {
            uchar pixel1 = src1.at<uchar>(h, w);  //bekijkt de pixel in ants1
            uchar pixel2 = src2.at<uchar>(h, w);  //bekijkt de pixel ins ants2
            uchar xorValue = pixel1 ^ pixel2;     
            dst.at<uchar>(h, w) = xorValue;
        }
    }
}