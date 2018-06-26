#include <stdio.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

/*
(18)HistogramEqualization.cpp

*/
Mat histogram(Mat src){
	Mat des;
	des.create(300, 255, CV_8UC1);
	
	for(int y = 0; y < des.rows; y++){
		for(int x = 0; x < des.cols; x++){
			des.at<uchar>(y,x) = 0;
		}
	}

	int arr[256];
	for(int i = 0; i < 255; i++){
		arr[i] = 0;
	}

	int mx = 0;
	for (int y = 0; y < src.rows; y++){
		for (int x = 0; x < src.cols; x++){
			int val = src.at<uchar>(y, x);
			arr[val]++;
		}
	}

	for (int i = 0; i < 255; i++) {
		if (arr[i] > mx) {
			mx = arr[i];
		}
	}


	for (int i = 0; i < 255; i++) {
		arr[i] = arr[i] * 300;
		arr[i] = arr[i] / mx;
	}

	for (int i = 0; i < 255; i++) {
		for (int j = 300 - arr[i]; j < 300; j++) {
			des.at<uchar>(j,i) = 255;
		}
	}

	return des;

}


Mat equalize(Mat src) {
	Mat des = src.clone();

	float array[256];
	for (int i = 0; i < 255; i++) {
		array[i] = 0;
	}


	for (int y = 0; y < des.rows; y++){
		for (int x = 0; x < des.cols; x++){
			int val = des.at<uchar>(y, x);
			array[val]++;
		}
	}
	
	int x = des.rows * des.cols;
	
	for (int i = 0; i < 255; i++) {
		array[i] = (float)array[i]/x;
	}
	
	float array2[256];
	float sum = 0.0;

	for (int i = 0; i < 255; i++) {
		sum = 0.0;
		for (int j = 0; j <= i; j++) {
			sum = sum + array[j];
		}
		array2[i] = sum;
	}

	for (int y = 0; y < des.rows; y++){
		for (int x = 0; x < des.cols; x++){
			int val = des.at<uchar>(y, x);
			float val2 = (float)255 * array2[val];
			val2 = ceil(val2);
			des.at<uchar>(y, x) = val2;
		}
	}
	
	return des;
}


int main(int argc, char const *argv[])
{
	Mat src = imread("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	imshow("Input", src);
	waitKey();

	Mat output = histogram(src);
	imshow("Primary Histogram Processing", output);
	waitKey();

	Mat eqlimg = equalize(src);
	imshow("Equalized Image", eqlimg);
	waitKey();

	Mat output2 = histogram(eqlimg);
	imshow("Equalized Histogram", output2);
	waitKey();

	return 0;
}