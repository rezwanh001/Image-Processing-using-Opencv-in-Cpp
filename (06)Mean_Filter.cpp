#include <stdio.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

/*
(06)Mean_Filter.cpp

*/

Mat spatFilter(double filter[3][3], Mat &img, int sob){
	int d = 3; // size of filter matrix
	Mat nimg(img.rows, img.cols, CV_8U, Scalar(0,0,0));

	for(int y = 0; y < img.rows ; y++){
		for(int x = 0; x < img.cols; x++){
			double val = 0;
			for(int r = 0; r < d; r++){
				for(int c = 0; c < d; c++){
					int rr = y + r - d/2;
					int cc = x + c - d/2;

					if (rr<0) rr=0;
                    if (cc<0) cc=0;
                    if (rr>=img.rows) rr=img.rows-1;
                    if (cc>=img.cols) cc=img.cols-1;

					val += filter[r][c]*(double)img.at<uchar>(rr, cc);
				}
			}
			if (sob == 1){
				nimg.at<uchar>(y, x) = saturate_cast<uchar>(abs(val));
			}
			else{
				nimg.at<uchar>(y, x) = saturate_cast<uchar>(val);
			}


		}
	}
	return nimg;

}

void meanFilter(Mat &img){
	double filter[3][3] = { {1,1,1}, {1,1,1}, {1,1,1} };

	int d = 3;
	for(int r = 0; r < d; r++){
		for(int c = 0; c < d; c++){
			filter[r][c] /= 9;
		}
	}

	Mat outImg = spatFilter(filter, img, 0);

	imshow("Mean Filter", outImg);
	waitKey();

}

int main(){
	// Take input image 
	Mat inImg = imread("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	imshow("Input Image", inImg);
	waitKey();

	// apply mean filter
	meanFilter(inImg);

	
   return 0;
}