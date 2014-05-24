#include "stdafx.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/background_segm.hpp>
#include "opencv/cv.h"
#include <stdio.h>
#include <iostream>
using namespace cv;
using namespace std;


int main(int argc, char* argv[])
{
  VideoCapture capture;	//For reading the Video
  BackgroundSubtractorMOG2 alpha;	//Displacement Mapping Construct
  Mat curr_frame = {}; //For Webcam Feed
  Mat Final = {};	//For Final Displacement Foreground
  capture.open(0);	//Videofeed is taken from Webcam
  capture.set(CV_CAP_PROP_FRAME_WIDTH, 640);	//Width and height is explicitly fixed for speed
  capture.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
  while (TRUE)
    {
      capture.read(curr_frame);	//Videofeed assigned to Matrix:curr_frame
      alpha.nmixtures = 5;	//Number of Gaussian Filters applied
      alpha.operator()(curr_frame, Final, 0.3);	//BacksubtractorMOG2 is applied and exported to Matrix:Final
      imshow("Final", Final);	//Shows both input Videofeed and Displacement Map
      imshow("Current", curr_frame);
      if(waitKey(30) >= 0) break;	//Exits if pressed esc for 30ms
    }
  return 0;
} 
