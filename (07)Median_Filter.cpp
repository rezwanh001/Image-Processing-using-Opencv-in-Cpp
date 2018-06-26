#include <stdio.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

/*
(07)Median_Filter.cpp

*/

void medianFilter(Mat &img){
	int d = 3; // size of filter matrix
	Mat nimg(img.rows, img.cols, CV_8U, Scalar(0,0,0)); // create a new image same size of input image.

	for(int y = 0; y < img.rows ; y++){
		for(int x = 0; x < img.cols; x++){
			vector <int> points;

			for(int r = 0; r < d; r++){
				for(int c = 0; c < d; c++){
					int rr = y + r - d/2;
					int cc = x + c - d/2;

					if (rr<0) rr=0;
                    if (cc<0) cc=0;
                    if (rr>=img.rows) rr=img.rows-1;
                    if (cc>=img.cols) cc=img.cols-1;

					points.push_back(img.at<uchar>(rr, cc));
				}
			}
			sort(points.begin(), points.end());

			nimg.at<uchar>(y,x) = points[d*d/2];


		}
	}
	img = nimg;

	imshow("Median Filter", img);
	waitKey();
	
}


int main(){
	// Take input image 
	Mat inImg = imread("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	imshow("Input Image", inImg);
	waitKey();

	// apply median filter
	medianFilter(inImg);

	
   return 0;
}