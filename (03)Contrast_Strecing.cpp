#include <stdio.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

/*
(03)Contrast_Strecing.cpp

You have given an input Image and co-ordinate of 2 points then you 
have to change of pixel with respect to co-ordinate. This method
is known as Contrest Stracing.
*/

int Contrast_Strecing(int pix, int r1, int s1, int r2, int s2){
	double res ;
	if (pix >= 0 && pix <= r1){
		res = (s1/r1) * pix;
	}
	else if (pix > r1 && pix <= r2){
		res = ( ((pix - r1)*(s2 - s1))/(r2 - r1) ) + s1;
	}
	else if (pix >r2 && pix <= 255){
		res = ( ((pix - r2)*(255 - s2))/(255 - r2) ) + s2;
	}
	return (int) res;
}


int main(){
   Mat src = imread("ab.tif");
   imshow("Input Image", src);
   waitKey();
  
   Mat dst = src.clone();
   imshow("Copy input image", dst);
   waitKey();

   // Enter the co-ordinate r1,s1, r2,s2;
   int r1,s1, r2,s2;
   cout << "Enter the co-ordinate (r1,s1), (r2,s2)" << endl;
   cin >> r1>>s1>> r2>>s2;

   for(int y=0; y<src.rows; y++){
	   for(int x = 0; x < src.cols; x++){
		   for(int c = 0; c < 3; c++){
			   int pixel = Contrast_Strecing(src.at<Vec3b>(y,x)[c], r1, s1, r2, s2);
			   dst.at<Vec3b>(y,x)[c] = saturate_cast<uchar>(pixel);
		   }
	   }
   }
   imshow("Contrast Strecing", dst);
   waitKey();

   return 0;
}

/*
For grayScale image. Load color image into grayScale image then 
operation on it.
*/
#include <stdio.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

/*
(03)Contrast_Strecing.cpp

You have given an input Image and co-ordinate of 2 points then you 
have to change of pixel with respect to co-ordinate. This method
is known as Contrest Stracing.
*/

int Contrast_Strecing(int pix, int r1, int s1, int r2, int s2){
	double res ;
	if (pix >= 0 && pix <= r1){
		res = (s1/r1) * pix;
	}
	else if (pix > r1 && pix <= r2){
		res = ( ((pix - r1)*(s2 - s1))/(r2 - r1) ) + s1;
	}
	else if (pix >r2 && pix <= 255){
		res = ( ((pix - r2)*(255 - s2))/(255 - r2) ) + s2;
	}
	return (int) res;
}


int main(){
   Mat src = imread("ab.tif", CV_LOAD_IMAGE_GRAYSCALE);
   imshow("Input Image", src);
   waitKey();
  
   Mat dst = src.clone();
   imshow("Copy input image", dst);
   waitKey();

   // Enter the co-ordinate r1,s1, r2,s2;
   int r1,s1, r2,s2;
   cout << "Enter the co-ordinate (r1,s1), (r2,s2)" << endl;
   cin >> r1>>s1>> r2>>s2;

   for(int y=0; y<src.rows; y++){
	   for(int x = 0; x < src.cols; x++){
			int pixel = Contrast_Strecing(src.at<uchar>(y,x), r1, s1, r2, s2);
			dst.at<uchar>(y,x) = saturate_cast<uchar>(pixel);
	   }
   }
   imshow("Contrast Strecing", dst);
   waitKey();

   return 0;
}