#include <stdio.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;


int main(){
   Mat inImg = imread("lena.jpg");
   imshow("Lena image",inImg);
   waitKey(0);

   return 0;
}