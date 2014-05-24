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
	VideoCapture capture;
	BackgroundSubtractorMOG2 alpha;
	Mat curr_frame = {};
	Mat Final = {};
	Mat imgTmp;	capture.read(imgTmp);
	Mat imgLines = Mat::zeros(imgTmp.size(), CV_8UC3);
	int iLastX = -1;
	int iLastY = -1;
	capture.open(0);
	capture.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
	while (TRUE)
	{
		capture.read(curr_frame);
		//cvtColor(curr_frame, curr_frame, CV_BGR2GRAY);
		//blur(curr_frame, curr_frame,Size(1,1));
		alpha.nmixtures = 5;
		alpha.operator()(curr_frame, Final, 0.3);
		//Calculate the moments of the thresholded image
		Moments oMoments = moments(Final);

		double dM01 = oMoments.m01;
		double dM10 = oMoments.m10;
		double dArea = oMoments.m00;

		// if the area <= 10000, I consider that the there are no object in the image and it's because of the noise, the area is not zero 
		if (dArea > 10000)
		{
			//calculate the position of the ball
			int posX = dM10 / dArea;
			int posY = dM01 / dArea;

			if (iLastX >= 0 && iLastY >= 0 && posX >= 0 && posY >= 0)
			{
				//Draw a red line from the previous point to the current point
				line(imgLines, Point(posX, posY), Point(iLastX, iLastY), Scalar(0, 0, 255), 2);
			}

			iLastX = posX;
			iLastY = posY;
		}
		imshow("Final", Final);
		curr_frame = curr_frame + imgLines;
		imshow("Current", curr_frame);
		if(waitKey(30) >= 0) break;
	}
	return 0;
} 
