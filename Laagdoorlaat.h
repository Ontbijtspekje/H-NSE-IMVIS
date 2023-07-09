#pragma once
#include "Laagdoorlaat.h"
using namespace cv;
using namespace std;

Laagdoorlaat::Laagdoorlaat(Mat& src, Mat& dst) {
    this->src = src;
    this->dst = dst;
    HEIGHT = src.rows;
    WIDTH = src.cols;
}

void Laagdoorlaat::process(void) {
    int h, w;
    for (h = 1; h < HEIGHT - 1; h++) {
        for (w = 1; w < WIDTH - 1; w++) {
            // filter = pixels * kernel
            /*
                  -1, -1  |  -1, 0  |  -1, +1
                  0, -1   |   0, 0  |   0, +1
                  +1, -1  |  +1, 0  |  +1, +1


             */
            int sum = -1 * src.at<uchar>(h - 1, w - 1) - src.at<uchar>(h - 1, w) - src.at<uchar>(h - 1, w + 1)
                - src.at<uchar>(h, w - 1) + 9 * src.at<uchar>(h, w) - src.at<uchar>(h, w + 1)
                - src.at<uchar>(h + 1, w - 1) - src.at<uchar>(h + 1, w) - src.at<uchar>(h + 1, w + 1);

            //max 255 en min 0 pixel value
            sum = std::max(0, std::min(sum, 255));

            dst.at<uchar>(h, w) = static_cast<uchar>(sum);
        }
    }
}
