#include "Threshold.h"

using namespace cv;
using namespace std;

Threshold::Threshold(Mat& src, Mat& dst) {
    this->src = src;
    this->dst = dst;
    HEIGHT = src.rows;
    WIDTH = src.cols;
}

 void Threshold::process(int thresholdValue) {
     int h, w;
     for (h = 1; h < HEIGHT - 1; h++) {
         for (w = 1; w < WIDTH - 1; w++) {
             int value = src.at<uchar>(h, w);
             if (value <= thresholdValue) {
                 value = 0;
             }
             else value = 255;
             dst.at<uchar>(h, w) = value;
         }
     }

  }
