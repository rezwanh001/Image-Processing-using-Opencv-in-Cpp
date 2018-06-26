#include <stdio.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

/*
(20)Thresholding.cpp

*/

int main(int argc, char const *argv[])
{
	Mat src = imread("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	imshow("Input", src);
	waitKey();

	Mat des = src.clone();
	
	int value;
	int total = 0;
	int intensity = 0;

	for(int y = 0; y < src.rows; y++){
		for(int x = 0; x < src.cols; x++){
			intensity = intensity + src.at<uchar>(y,x);
			total += 1;
		}
	}

	value = 50;

	int upper = 0, c1 = 0, lower = 0, c2 = 0;
	int m1, m2;
	int Tp;
	int diff = 10;

	string abc = "abc";

	for(int i = 0; i < 10; i++){

		for(int y = 0; y < src.rows; y++){
			for(int x  = 0; x < src.cols; x++){
				if(src.at<uchar>(y, x) >= 0 && src.at<uchar>(y, x) <= value){
					des.at<uchar>(y, x) = 0;
				}
				else if(src.at<uchar>(y, x) >127 && src.at<uchar>(y, x) <= 255){
					des.at<uchar>(y, x) = 255;
				}
			}
		}
		imshow(abc, des);
		abc = abc + abc;

		for(int y = 0; y < src.rows; y++){
			for(int x  = 0; x < src.cols; x++){
				if(src.at<uchar>(y, x) >= 0 && src.at<uchar>(y, x) <= value){
					lower = lower + src.at<uchar>(y,x);
					c1 += 1;
				}
				else if(src.at<uchar>(y, x) >127 && src.at<uchar>(y, x) <= 255){
					upper = upper + src.at<uchar>(y,x);
					c2 += 1;
				}
			}
		}

		m1 = (upper / c2);
		m2 = (lower / c1);
		Tp = (m1 + m2) / 2;

		if(abs(value - Tp) < diff){
			break;
		}

		value = Tp;
		upper = 0;
		c1 = 0;
		lower = 0;
		c2 = 0;

		cout << value << " " ;
	}

	waitKey();
	
	return 0;
}