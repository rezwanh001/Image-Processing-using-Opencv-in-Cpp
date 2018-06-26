#include <stdio.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

/*
(09,10)Min_Max_Filter.cpp

*/

int main(int argc, char const *argv[])
{
	Mat img = imread("blurry_moon.tif", CV_LOAD_IMAGE_GRAYSCALE);
	imshow("Input", img);
	waitKey();

	// Average filter
	Mat avgImage ;
	boxFilter(img, avgImage, -1, Size(3,3)); // // Perform mean filtering on image using boxfilter
	imshow("Average Filter", avgImage);
	waitKey();

	// The functions "erode" and "dilate" are min and max filters, respectively.

	Mat ker;   // Use the default structuring element (kernel) for erode and dilate

	// Min Filter
	Mat minImage;
	erode(img, minImage, ker);
	imshow("Min Filter", minImage);
	waitKey();

	// Max filter
	Mat maxImage;
	dilate(img, maxImage, ker);
	imshow("Max Filter", minImage);
	waitKey();
	/*********************/

	float kdata4[9] = {
		0, -1, 0,
		-1,4, -1,
		0,-1,0
	};

	Mat kernel = Mat(3, 3, CV_32F, kdata4);

	
	Mat out, out2;	
	filter2D(img, out, CV_32F, kernel, Point(-1, -1));
	imshow("Filter", out);
	waitKey();

	out2 = abs(out);
	imshow("Abs Filter", out2);
	waitKey();

	Mat out3;
	normalize(out2, out3, 0, 255, NORM_MINMAX, CV_8U);
	imshow("NormMin_MAx", out3);
	waitKey();

	Mat fin = img + out3;
	imshow("Final", fin);
	waitKey();
	

	return 0;
}