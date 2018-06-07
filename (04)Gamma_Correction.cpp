#include <stdio.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

/*
(04)Gamma_Correction.cpp

s = c*r^(gamma)

*/

int Gamma_Correction(int pix, int C, int gamma){
	double res ;
	res = C * pow(pix, gamma);
	res = (res / (C * pow(255, gamma))) * 255; // Normalized if res > 255
	
	return (int) res;
}


int main(){
   Mat src = imread("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
   imshow("Input Image", src);
   waitKey();
  
   Mat dst = src.clone();
   
   double C, gamma;
   cout << "Enter Constant: "; cin >> C;
   cout << "Enter Gamma: " ; cin >> gamma;

   for(int y = 0; y < src.rows; y++){
	   for(int x = 0; x < src.cols; x++){
		   int pix = Gamma_Correction(src.at<uchar>(y,x), C, gamma);
		   dst.at<uchar>(y,x) = saturate_cast<uchar>(pix);
	   }
   }

   imshow("Gamma Correction", dst);
   waitKey();

   return 0;
}