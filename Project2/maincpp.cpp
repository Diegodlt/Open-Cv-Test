#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/videoio.hpp>

#include "Histogram1D.h"

using namespace std;
using namespace cv;

const int sliderMaxBrightness = 300;
const int sliderMaxContrast = 400;
int sliderBrightness = 150;
int sliderContrast = 100;
double contrast = 1.0;
double brightness = 0;
Histogram1D h;

cv::Mat3b canvas;
string buttonText = "Save";
string winName = "Controls";
cv::Rect button;

bool saveVideo = false;

static void on_trackbarContrast(int, void*) {
	
	contrast = (double)sliderContrast/100;

}

static void on_trackbarBrightness(int, void*) {

	brightness = (double)sliderBrightness - 150;
	
}

void callBackFunc(int event, int x, int y, int flags, void* userdata)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		if (button.contains(Point(x, y)))
		{
			cout << "Screen will close at the end of video" << endl;
			saveVideo = true;
			rectangle(canvas(button), button, Scalar(0, 0, 255), 2);
		}
	}
	if (event == EVENT_LBUTTONUP)
	{
		rectangle(canvas, button, Scalar(200, 200, 200), 2);
	}

	imshow(winName, canvas);
	waitKey(1);
}

int main() {

	// An image
	Mat3b img(50, 300, Vec3b(0, 0, 0));

	// Your button
	button = Rect(0, 0, img.cols, 50);

	// The canvas
	canvas = Mat3b(img.rows + button.height, img.cols, Vec3b(0, 0, 0));

	// Draw the button
	canvas(button) = Vec3b(200, 200, 200);
	putText(canvas(button), buttonText, Point(button.width*0.35, button.height*0.7), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 0));

	// Draw the image
	img.copyTo(canvas(Rect(0, button.height, img.cols, img.rows)));

	// Setup callback function
	namedWindow(winName);
	setMouseCallback(winName, callBackFunc);

	imshow(winName, canvas);

	while (1) {

		if (saveVideo) {
			break;
		}
		cv::VideoCapture inputVideo("barriers.avi");
		// Check if camera opened successfully
		if (!inputVideo.isOpened()) {
			cout << "Error opening video stream or file" << endl;
			return -1;
		}

		int ex = static_cast<int>(inputVideo.get(CAP_PROP_FOURCC));
		char EXT[] = { (char)(ex & 0XFF) , (char)((ex & 0XFF00) >> 8),(char)((ex & 0XFF0000) >> 16),(char)((ex & 0XFF000000) >> 24), 0 };
		cv::Size S = cv::Size(
			(int)inputVideo.get(CAP_PROP_FRAME_WIDTH),
			(int)inputVideo.get(CAP_PROP_FRAME_HEIGHT)
		);

		cv::VideoWriter outputVideo;
		outputVideo.open("output.avi", ex, inputVideo.get(CAP_PROP_FPS), S, true);
		if (!outputVideo.isOpened())
		{
			cout << "Could not open the output video for write" << endl;
			return -1;
		}

		while (1) {

			cv::Mat frame;
			// inputVideoture frame-by-frame
			inputVideo >> frame;

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

			outputVideo.write(newImage);

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

		// When everything done, release the video inputVideoture object
		inputVideo.release();

	}

	// Closes all the frames
	cv::destroyAllWindows();
	cv::waitKey(0);
	system("PAUSE");
	return 0;
}

