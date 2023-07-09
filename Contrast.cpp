#include "Contrast.h"

using namespace cv;
using namespace std;

Contrast::Contrast(Mat& src, Mat& dst) {
    this->src = src;
    this->dst = dst;
    HEIGHT = src.rows;
    WIDTH = src.cols;
}

void Contrast::process(void) {
    int h, w, temp = 0;
    for (h = 0; h < HEIGHT; h++) {
        for (w = 0; w < WIDTH; w++) {

            temp = src.at<uchar>(h, w);
            dst.at<uchar>(h, w) = ((float)(temp - 3) / (95 - 3)) * 255;
            //formule uit de powerpoint max en min grijswaarde vanuit de histogram
          
            
        }
    }
}
