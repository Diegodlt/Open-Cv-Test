#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc.hpp>

#include "Histogram1D.h"

using namespace std;

int main() {

	cv::Mat image = cv::imread("einstein.jpg", 0); // read in black and white
	imshow("Image", image);

	if (image.empty()) {
		cout << "Empty image" << endl;
		return 0;
	}

	Histogram1D h;

	cv::namedWindow("Histogram");
	cv::imshow("Histogram", h.getHistorgramImage(image, 2));

	cv::Mat histo = h.getHistogram(image);

	// Loop over each bin
	for (int i = 0; i < 256; i++) {
		cout << "Value " << i << "=" << histo.at<float>(i) << endl;
	}

	cv::waitKey(0);
	system("PAUSE");
	return 0;
}
