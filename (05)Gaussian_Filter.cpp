#include <stdio.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

/*
(05)Gaussian_Filter.cpp

*/

Mat inImg, filter, outImg, maskMat, unsharpMask;


void gaussianFilter(float sigma, int maskSize){
	float sigmaSq = (sigma * sigma);

	int s = maskSize / 2;

	float norm = (1.0/(2*3.14*sigmaSq));
	float val;

	for(int y = -s, y1 = 0; y <= s; y++, y1++){
		for(int x = -s, x1 = 0; x <= s; x++, x1++){
			val = norm * exp( (-( (x*x) + (y*y) )) / (2 * sigmaSq) ); // Write this line correctly
			filter.at<float>(y1, x1) = val;
		}
	}

}

void applyGaussian(int s){
	float a;
	for(int y=s; y < inImg.rows - s; y++){
		for(int x = s; x < inImg.cols - s; x++){
			a = 0.0;
			for(int y1=-s, y2 = 0; y1 <= s; y1++, y2++){
				for(int x1=-s, x2=0; x1 <= s; x1++, x2++){
					a += (float) inImg.at<uchar>(y+y1, x+x1) * filter.at<float>(y2, x2);
				}
			}
			outImg.at<uchar> (y-s, x-s) = (uchar) a;
		}
	}
}



int main(){
	// Take input image 
	inImg = imread("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	imshow("Input Image", inImg);
	waitKey();

	float sigma;
	cout << "Enter Sigma: " ; cin >> sigma;

	int maskSize = (int) sigma * 5.0;
	if (maskSize % 2 == 0) {
		maskSize += 1;
	}
	// create gaussian filter
	filter.create(maskSize, maskSize, CV_32FC1);

	// Gaussian Filter
	gaussianFilter(sigma, maskSize);

	int s = maskSize / 2;
	// Create output image
	outImg.create(inImg.rows - s, inImg.cols - s, inImg.type());
	unsharpMask = outImg;
	/*
	imshow("unsharpMask Filter", unsharpMask);
	waitKey();
	*/
	// apply Gaussian operation on image
	applyGaussian(s);

	imshow("Gaussian Filter", outImg);
	waitKey();

   return 0;
}