#include <stdio.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

/*
(16)Boundary_Extraction.cpp

*/

Mat erosion(Mat dst, int maskSize){
	int s;
	s = maskSize / 2;
	Mat mask;
	mask.create(maskSize, maskSize, CV_32S);
	Mat out;
	out.create(dst.size(), dst.type());

	int flag = 0;
	for(int y=0; y < dst.rows - maskSize + 1; y++){
		for(int x = 0; x < dst.cols - maskSize + 1; x++){
			flag = 0;
			for(int y1 = 0; y1 < maskSize ; y1++){
				for(int x1 = 0; x1 < maskSize; x1++){
					if(dst.at<uchar>(y + y1, x + x1) != 255){
						flag = 1;
					}
				}
			}
			if (flag == 1){
				out.at<uchar> (y+s, x+s) = 0;
			}
			else{
				out.at<uchar>(y+s, x+s) = dst.at<uchar>(y+s, x+s);
			}
		}
	}
	return out;
}


int main(int argc, char const *argv[])
{
	Mat src = imread("linkon.tif", CV_LOAD_IMAGE_GRAYSCALE);
	imshow("Input", src);
	waitKey();

	int maskSize;
	cout << "Enter mask Size:" ;
	cin>> maskSize;
	Mat dst;
	int s;
	s = maskSize / 2;
	copyMakeBorder(src, dst, s,s,s,s, 0,0);

	// thresholding for Binary Image
	for(int y = 0; y < dst.rows; y++){
		for(int x = 0; x < dst.cols; x++){
			if(dst.at<uchar>(y,x) >= 0 && dst.at<uchar>(y,x) <= 127){
				dst.at<uchar>(y, x) = 0;
			}
			else if(dst.at<uchar>(y, x) >127 && dst.at<uchar>(y, x) <= 255){
				dst.at<uchar>(y, x) = 255;
			}
		}
	}

	// Erosion of an Image
	Mat output = erosion(dst, maskSize);
	imshow("After Erosion", output);
	waitKey();

	// Boundary Extraction
	Mat bounImg;
	bounImg.create(dst.size(), dst.type());
	for(int y = 0; y < dst.rows; y++){
        for(int x = 0; x < dst.cols; x++){
            bounImg.at<uchar>(y, x) = dst.at<uchar>(y, x) - output.at<uchar>(y, x);
        }
    }

    imshow("Boundary Extraction", bounImg);
    waitKey(0);

	return 0;
}