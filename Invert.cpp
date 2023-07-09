#include "Invert.h"
using namespace cv;
using namespace std;

Invert::Invert(Mat& src, Mat& dst) {
    this->src = src;
    this->dst = dst;
    HEIGHT = src.rows;
    WIDTH = src.cols;
}

void Invert::process(void) {
    int h, w, temp = 0;
    for (h = 0; h < HEIGHT; h++) {
        for (w = 0; w < WIDTH; w++) {

            temp = src.at<uchar>(h, w);
            
            dst.at<uchar>(h, w) = 255 - temp;
            // door de grijswaarde - 255 (max pixel size) te doen wordt de de grijswaarde geinventeerd 
        }
    }
}