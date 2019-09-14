#include "Histogram1D.h"
#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc.hpp>

using namespace std;


Histogram1D:: Histogram1D()
{
	histSize[0] = 256; // 256 bins
	hranges[0] = 0.0; // from 0 (inclusive)
	hranges[1] = 256.0; // to 256 (exclusive)
	ranges[0] = hranges;
	channels[0] = 0; // we look at channel 0
}

cv::Mat Histogram1D::getHistogram(const cv::Mat &image)
{

	cv::Mat hist;

	//Comput histogram
	cv::calcHist(
		&image,
		1, // histogram of 1 image only
		channels, // the channel used
		cv::Mat(), // no mask is used
		hist, // the resulting historgram
		1, // it is a 1D histogram
		histSize, // number of bins
		ranges // pixel value range
	);
	return hist;
}
