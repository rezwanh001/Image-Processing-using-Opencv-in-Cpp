#include <stdio.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

/*
Input image convert into Negative Image.
--- Convert a BGR image into Gray image then subtract each pixel of
	gray level from 255. i.e, r = 255 - s 
(02)NegativeImage.cpp
*/

int main(){
   Mat inImg = imread("lena.jpg");
   imshow("Lena image",inImg);
   waitKey();

   Mat grayLena;
   cvtColor(inImg, grayLena, CV_BGR2GRAY);
   imshow("Gray Lena", grayLena);
   waitKey();

   int y,x, r,s;
   for(y=0; y<grayLena.rows; y++){
	   for(x=0; x<grayLena.cols; x++){
		   s = grayLena.at<uchar>(y, x);
		   r = 255 - s;
		   grayLena.at<uchar>(y, x) = r;
	   }
   }
   imshow("Negative Image", grayLena);
   waitKey();

   return 0;
}