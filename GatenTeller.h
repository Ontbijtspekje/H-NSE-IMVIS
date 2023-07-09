#pragma once
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

class GatenTeller {
public:
	GatenTeller(Mat& src);
	void tellen();
	int process();
	uint8_t labelPixel(int h, int w);
private:
	Mat src,dst;
	int HEIGHT, WIDTH;
	uint8_t Label;
};

