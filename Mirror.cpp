#include "Mirror.h"
using namespace cv;
using namespace std;

Mirror::Mirror(Mat& src, Mat& dst) {
    this->src = src;
    this->dst = dst;
    HEIGHT = src.rows;
    WIDTH = src.cols;
}

void Mirror::process(void){
	int h, w, temp = 0;
    for (h = 0; h < HEIGHT; h++) {
        for (w = 0; w < WIDTH; w++) {

            temp = src.at<uchar>(h, w);
            //temp = *src.ptr(h, w); // hetzelfde als hierboven, maar op een ander manier.

            dst.at<uchar>(h, WIDTH - w - 1 ) = temp;
            //*dst.ptr(HEIGHT - h - 1, w) = temp; // hetzelfde als hierboven, maar op een andere manier.
            // als height - h - 1 ervoor zorgt dat de afbeelding verticaal gespiegeld wordt, zorgt width - w - 1 ervoor dat de afbeelding horizontaal gespiegeld wordt
        }
    }
}