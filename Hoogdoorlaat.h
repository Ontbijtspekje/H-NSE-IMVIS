#pragma once
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

class Hoogdoorlaat {
public:
	Hoogdoorlaat(Mat& src, Mat& dst);
	void process(void);
private:
	Mat src, dst;
	int HEIGHT, WIDTH;
	//int kernel[9] = { -1, -1, -1, 0, 0, 0, 1, 1, 1 }; // Kernel represented as an array
};

