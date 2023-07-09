#include "Hoogdoorlaat.h"
using namespace cv;
using namespace std;

Hoogdoorlaat::Hoogdoorlaat(Mat& src, Mat& dst) {
    this->src = src;
    this->dst = dst;
    HEIGHT = src.rows;
    WIDTH = src.cols;

}

void Hoogdoorlaat::process(void) {
 /*
    
            
                  -1, -1  |  -1, 0  |  -1, +1
                  0, -1   |   0, 0  |   0, +1
                  +1, -1  |  +1, 0  |  +1, +1
                 int sum = -1 * src.at<uchar>(h - 1, w - 1) - src.at<uchar>(h - 1, w) - src.at<uchar>(h - 1, w + 1)
                - src.at<uchar>(h, w - 1) + 9 * src.at<uchar>(h, w) - src.at<uchar>(h, w + 1)
                - src.at<uchar>(h + 1, w - 1) - src.at<uchar>(h + 1, w) - src.at<uchar>(h + 1, w + 1);

  */
            

    int h, w;
    int matrix[9] = { -1, -1, -1, -1, 9, -1, -1, -1, -1 }; //matrix hoogdoorlaat

    for (h = 1; h < HEIGHT - 1; h++) {
        for (w = 1; w < WIDTH - 1; w++) {
            int sum = 0;
            int k = 0;
            for (int i = -1; i <= 1; i++) {              //matrix voor pixels
                for (int j = -1; j <= 1; j++) {
                    sum += matrix[k] * src.at<uchar>(h + i, w + j);
                    k++;
                }
            }

            sum = std::max(0, std::min(sum, 255)); //pixel value

            dst.at<uchar>(h, w) = static_cast<uchar>(sum);
        }
    }
}