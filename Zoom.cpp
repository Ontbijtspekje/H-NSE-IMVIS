#include "Zoom.h"

using namespace cv;
using namespace std;

Zoom::Zoom(Mat& src, Mat& dst) {
    this->src = src;
    this->dst = dst;
    HEIGHT = src.rows;
    WIDTH = src.cols;
}


void Zoom::process(float keer) {
    int zoomedHeight = static_cast<int>(HEIGHT * keer);
    int zoomedWidth = static_cast<int>(WIDTH * keer);

    int h, w, temp = 0;

    if (keer >= 1) {   
        //zoom in, groter dan 1
        //zoomfactor + coordinaten
        zoomedHeight = static_cast<int>(HEIGHT * keer);
        zoomedWidth = static_cast<int>(WIDTH * keer);
        // For each pixel in the destination image :
        for (h = 0; h < HEIGHT; h++) {
            for (w = 0; w < WIDTH; w++) {
                //static cast for float to integer
                int srcH = static_cast<int>(h / keer);
                int srcW = static_cast<int>(w / keer);

                dst.at<uchar>(h, w) = src.at<uchar>(srcH, srcW);
            }
        }

    }
    else {
        //zoom out kleiner dan 1

        int startX = (WIDTH - zoomedWidth) / 2;
        int startY = (HEIGHT - zoomedHeight) / 2;

        dst.setTo(255);

        //witte rand en in het midden verbeeld
        for (h = 0; h < zoomedHeight; h++) {
            for (w = 0; w < zoomedWidth; w++) {
   
                //static cast for float to integer
                int srcH = static_cast<int>(h / keer);
                int srcW = static_cast<int>(w / keer);

                // Check if the coordinates are within the original image bounds
                if (srcH < HEIGHT && srcW < WIDTH) {
                    dst.at<uchar>(startY + h, startX + w) = src.at<uchar>(srcH, srcW);
                }
            }
        }
    }
}


