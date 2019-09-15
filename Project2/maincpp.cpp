#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc.hpp>

#include "Histogram1D.h"

using namespace std;
using namespace cv;

const int sliderMaxBrightness = 200;
const int sliderMaxContrast = 400;
int sliderBrightness = 0;
int sliderContrast = 100;
double contrast = 1.0;
double brightness;
Histogram1D h;

static void on_trackbarContrast(int, void*) {
	
	contrast = (double)sliderContrast/100;

}

static void on_trackbarBrightness(int, void*) {

	brightness = (double)sliderBrightness;
	
}

int main() {

	cv::VideoCapture cap("barriers.avi");

	// Check if camera opened successfully
	if (!cap.isOpened()) {
		cout << "Error opening video stream or file" << endl;
		return -1;
	}

	while (1) {

		cv::Mat frame;
		// Capture frame-by-frame
		cap >> frame;

		// If the frame is empty, break immediately
		if (frame.empty())
			break;

		cv::Mat newImage = cv::Mat::zeros(frame.size(), frame.type());

		for (int y = 0; y < newImage.rows; y++) {
			for (int x = 0; x < newImage.cols; x++) {
				for (int c = 0; c < newImage.channels(); c++) {
					newImage.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(contrast*frame.at<Vec3b>(y, x)[c] + brightness);
				}
			}
		}

		char TrackbarOne[50];
		sprintf_s(TrackbarOne, "Contrast");
		cv::createTrackbar(TrackbarOne, "Image", &sliderContrast, sliderMaxContrast, on_trackbarContrast);

		char TrackbarTwo[50];
		sprintf_s(TrackbarTwo, "Brightness");
		cv::createTrackbar(TrackbarTwo, "Image", &sliderBrightness, sliderMaxBrightness, on_trackbarBrightness);

		cv::Mat histo = h.getHistogram(newImage);
		imshow("Histogram", h.getHistorgramImage(newImage, 2));

		// Display the resulting frame
		cv::imshow("Image", newImage);
		cv::imshow("Video", frame);

		// Press  ESC on keyboard to exit
		char c = (char)waitKey(25);
		if (c == 27)
			break;
	}

	// When everything done, release the video capture object
	cap.release();

	// Closes all the frames
	destroyAllWindows();

	cv::waitKey(0);
	return 0;
}

