/*		TO DO		
Reset the imgLines matrix is left unchanged after 2 seconds - DONE
Re-initialize the matrix - DONE
Record Gesture by zero threshold - DONE
Record Gesture information in string - DONE
Compare Gesture string with pre-defined function string. - DONE
Translate the function string into actual string. - DONE
Optimizing Cap tracing.
*/	

#include "stdafx.h"
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <sstream>
#include <stdlib.h>
#include <Windows.h>
#include <WinUser.h>

using namespace cv;
using namespace std;
using namespace std;

void keystroke(char*);

int main(int argc, char** argv)
{
	int flag = 0;
	VideoCapture cap(0); //Capture the video from webcam

	if (!cap.isOpened())  // if not success, exit program
	{
		cout << "Cannot open the web cam" << endl;
		return -1;
	}
	//Filename
	int ct = 0;
	stringstream ss;
	string name = "Track";
	string type = ".png";
	ss << name << (ct + 0) << type;
	string filename = ss.str();
	
	namedWindow("Control", CV_WINDOW_NORMAL); //create a window called "Control"

	//Color co-ordinates for orange
	int iLowH = 0;
	int iHighH = 212;

	int iLowS = 125;
	int iHighS = 237;

	int iLowV = 186;
	int iHighV = 255;

	//Create trackbars in "Control" window
	createTrackbar("LowH", "Control", &iLowH, 255); //Hue (0 - 255)
	createTrackbar("HighH", "Control", &iHighH, 255);

	createTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
	createTrackbar("HighS", "Control", &iHighS, 255);

	createTrackbar("LowV", "Control", &iLowV, 255);//Value (0 - 255)
	createTrackbar("HighV", "Control", &iHighV, 255);

	//Position variables
	int posX;
	int posY;
	int iLastX = -1;
	int iLastY = -1;
	int X;
	int Y;
	int i = 0;
	int j = 0;
	int gestnum = 0;
	char *recognize = (char*)calloc(5, sizeof(int));

	//Capture a temporary image from the camera
	Mat imgTmp;
	cap.read(imgTmp);

	//Create a black image with the size as the camera output
	Mat imgLines = Mat::zeros(imgTmp.size(), CV_8UC3);

	//Record keeping variable
	int record = 0;

	while (true)
	{
		Mat imgOriginal;

		bool bSuccess = cap.read(imgOriginal); // read a new frame from video

		if (!bSuccess) //if not success, break loop
		{
			cout << "Cannot read a frame from video stream" << endl;
			break;
		}

		Mat imgHSV;

		cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

		Mat imgThresholded;

		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image

		//morphological opening (removes small objects from the foreground)
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		//morphological closing (removes small holes from the foreground)
		dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		//Calculate the moments of the thresholded image
		Moments oMoments = moments(imgThresholded);

		double dM01 = oMoments.m01;
		double dM10 = oMoments.m10;
		double dArea = oMoments.m00;

		// if the area <= 10000, I consider that the there are no object in the image and it's because of the noise, the area is not zero 
		if (dArea > 10000)
		{
			//calculate the position of the ball
			posX = (int)dM10 / dArea;
			posY = (int)dM01 / dArea;

			if (iLastX >= 0 && iLastY >= 0 && posX >= 0 && posY >= 0)
			{
				//Draw a red line from the previous point to the current point
				line(imgLines, Point(posX, posY), Point(iLastX, iLastY), Scalar(0, 0, 255), 2);
			}

			record++;
			X = posX - iLastX;
			Y = posY - iLastY;
			if (i == 0)
			{
				i++;
			}
			else	//Assign ASCII code for direction letters - u d l r
			{
				if (X > 20 && Y < 20 && Y > -20)
				{
					//printf("Left\n");
					gestnum = 108;
				}
				if (X < -20 && Y < 20 && Y > -20)
				{
					//printf("Right\n");
					gestnum = 114;
				}

				if (Y > 20 && X < 20 && X > -20)
				{
					//printf("Down\n");
					gestnum = 100;
				}
				if (Y < -20 && X < 20 && X > -20)
				{
					//printf("Up\n");
					gestnum = 117;
				}
			}

			iLastX = posX;
			iLastY = posY;
		}

		if (dArea == 0.00 && record != 0 || j == 3)
		{
			printf("Gesture recorded!\n");
			recognize[0] = 'g';		//Inherently, first element will be NULL if we don't do this
			printf("%s\n", recognize);
			keystroke(recognize);		//Keystroke function. See keystroke.cpp
			imgLines = Mat::zeros(imgTmp.size(), CV_8UC3);	//Resetting the threshold matrix
			record = 0;
			iLastX = -1;
			iLastY = -1;
			i = 0;
			j = 0;
			gestnum = 0;
			free(recognize);
			recognize = (char*)calloc(5, sizeof(int));
			Sleep(500); //idles the program for 2 seconds. Enough time to zero out the threshold
		}
		
		if (recognize[j] != gestnum)		//Recording direction to the gesture array
		{
			j++;
			recognize[j] = gestnum;
		}

		imshow("Thresholded Image", imgThresholded); //show the thresholded image

		imgOriginal = imgOriginal + imgLines;
		imshow("Original", imgOriginal); //show the original image

		if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}
	}

	return 0;
}
