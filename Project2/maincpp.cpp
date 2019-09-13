#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main() {

	Mat image = imread("GS.jpg");
	imshow("Image", image);

	waitKey(0);
	return 0;
}