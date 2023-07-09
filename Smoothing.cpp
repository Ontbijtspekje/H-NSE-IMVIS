#include "Smoothing.h"

using namespace cv;
using namespace std;

Smoothing::Smoothing(Mat& src, Mat& dst) {
    this->src = src;
    this->dst = dst;
    HEIGHT = src.rows;
    WIDTH = src.cols;
}

void Smoothing::process(void) {
    int h, w;
    int matrix[9] = { 1, 1, 1, 1, 1, 1, 1, 1, 1 }; 

    for (h = 1; h < HEIGHT - 1; h++) {
        for (w = 1; w < WIDTH - 1; w++) {
            int sum = 0;
            int k = 0;
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    sum += matrix[k] * src.at<uchar>(h + i, w + j); //optellen pixelwaarde
                    k++;
                }
            }

            sum /= 9; //gemiddelde van som krijgen

            sum = std::max(0, std::min(sum, 255)); //afbakenen

            dst.at<uchar>(h, w) = static_cast<uchar>(sum);
        }
    }
}
