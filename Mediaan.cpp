#include "Mediaan.h"
using namespace cv;
using namespace std;

Mediaan::Mediaan(Mat& src, Mat& dst) {
    this->src = src;
    this->dst = dst;
    HEIGHT = src.rows;
    WIDTH = src.cols;
}

void Mediaan::process(void) {
    int h, w;
    for (h = 1; h < HEIGHT - 1; h++) {
        for (w = 1; w < WIDTH - 1; w++) {
            int k = 0;
            int values[9];
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    values[k] = src.at<uchar>(h + i, w + j); //pixelwaardes in array
                    k++;
                }
            }

            //waardes op laten tellen
            for (int i = 0; i < 9 - 1; i++) {
                for (int j = 0; j < 9 - i - 1; j++) {
                    if (values[j] > values[j + 1]) {
                        int temp = values[j];
                        values[j] = values[j + 1];
                        values[j + 1] = temp;
                    }
                }
            }

            int median = values[4]; //middelste waarde = mediaan

            dst.at<uchar>(h, w) = static_cast<uchar>(median);
        }
    }
}