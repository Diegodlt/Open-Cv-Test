#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc.hpp>

#include "Histogram1D.h"

using namespace std;
using namespace cv;

const int sliderMaxBrightness = 200;
const int sliderMaxContrast = 40;
int sliderBrightness;
int sliderContrast = 10;
double contrast = 0;
double brightness = 0;
cv::Mat image;
cv::Mat dest;
Histogram1D h;

static void on_trackbarContrast(int, void*) {
	
	contrast = (double)sliderContrast/10;
	cout << "Contrast " << contrast << endl;
	cv::Mat newImage = cv::Mat::zeros(image.size(), image.type());

	for (int y = 0; y < newImage.rows; y++) {
		for (int x = 0; x < newImage.cols; x++) {
			for (int c = 0; c < newImage.channels(); c++) {
				newImage.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(contrast*image.at<Vec3b>(y, x)[c] + brightness);
			}
		}
	}

	cv::Mat histo = h.getHistogram(newImage);
	imshow("Histogram", h.getHistorgramImage(newImage, 2));
	imshow("Image", newImage);
}

static void on_trackbarBrightness(int, void*) {

	brightness = (double)sliderBrightness;
	cv::Mat newImage = cv::Mat::zeros(image.size(), image.type());

	for (int y = 0; y < newImage.rows; y++) {
		for (int x = 0; x < newImage.cols; x++) {
			for (int c = 0; c < newImage.channels(); c++) {
				newImage.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(contrast*image.at<Vec3b>(y, x)[c] + brightness);
			}
		}
	}

	cv::Mat histo = h.getHistogram(newImage); 
	imshow("Histogram", h.getHistorgramImage(newImage, 2));
	imshow("Image", newImage);
}

int main() {

	//Histogram1D h;

	image = cv::imread("einstein.jpg"); 
	if (image.empty()) {
		cout << "Empty image" << endl;
		return 0;
	}
	cv::Mat histo = h.getHistogram(image);

	cv::imshow("Image", image);

	cv::namedWindow("Histogram");
	cv::imshow("Histogram", h.getHistorgramImage(image, 2));


	char TrackbarOne[50];
	sprintf_s(TrackbarOne, "Contrast");
	cv::createTrackbar(TrackbarOne, "Image", &sliderContrast, sliderMaxContrast, on_trackbarContrast);

	char TrackbarTwo[50];
	sprintf_s(TrackbarTwo, "Brightness");
	cv::createTrackbar(TrackbarTwo, "Image", &sliderBrightness, sliderMaxBrightness, on_trackbarBrightness);


	cv::waitKey(0);
	system("PAUSE");
	return 0;
}

