#pragma once
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc.hpp>

class Histogram1D
{
public:
	private:
		int histSize[1]; //number of bins in histogram
		float hranges[2]; //range of values
		const float* ranges[1]; // pointer to the value ranges
		int channels[1]; // channel number to be examined
	
	public:
		// Prepare default arguments for 1D histogram
		Histogram1D();
		cv::Mat getHistogram(const cv::Mat &image);
		cv::Mat getHistorgramImage(const cv::Mat & image, int zoom);
		cv::Mat getImageOfHistogram(const cv::Mat & hist, int zoom);
};

