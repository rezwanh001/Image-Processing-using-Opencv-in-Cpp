#include <stdio.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

/*
(19)FourierTransform_DFT.cpp

Source: https://github.com/rksazid/Image-Processing/blob/master/Discreate%20Fourier%20Transform%20(dft).cpp.cpp

*/



int main(int argc, char const *argv[])
{
	Mat src = imread("dft.png", CV_LOAD_IMAGE_GRAYSCALE);
	imshow("Input", src);
	waitKey();

	Mat padded; // expand input image to optimal size
	int m = getOptimalDFTSize(src.rows);
	int n = getOptimalDFTSize(src.cols); // on the border add zero values
	copyMakeBorder(src, padded, 0, m - src.rows, 0, n - src.cols, BORDER_CONSTANT, Scalar::all(0));

	Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
	Mat complexI;

	merge(planes, 2, complexI); // add to the expanded another plane with zeros
	
	dft(complexI, complexI); // this way the result may fit in the source matrix

	// compute the magnitude and switch to logarithmic scale
	//  log(1 + sqrt(Re(DFT(src))^2 + Im(DFT(I))^2)
	split(complexI, planes); // // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
	magnitude(planes[0], planes[1], planes[0]); // // planes[0] = magnitude
	Mat magI = planes[0];

	magI += Scalar::all(1); // Switch to logarithmic scale
	log(magI, magI);

	// crop the spectrum, if it has an odd number of rows or columns
	magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));

	//re-arrange the quadrants of Fourier imag eso tht the origin is at the image center
	int cx = magI.cols / 2; 
	int cy = magI.rows / 2;

	Mat q0(magI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
    Mat q1(magI, Rect(cx, 0, cx, cy));  // Top-Right
    Mat q2(magI, Rect(0, cy, cx, cy));  // Bottom-Left
    Mat q3(magI, Rect(cx, cy, cx, cy)); // Bottom-Right

	Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
    q2.copyTo(q1);
    tmp.copyTo(q2);

	normalize(magI, magI, 0, 1, CV_MINMAX); //Transform the matrix with float values into a viewable image form (float between values 0 and 1).
	imshow("DFT Spectrum", magI);
	waitKey();

	return 0;
}