#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/background_segm.hpp>
#include "opencv/cv.h"
#include <stdio.h>
#include <iostream>
using namespace cv;
using namespace std;

BackgroundSubtractorMOG2 alpha;

Mat curr_frame ;

Mat Final ;

Mat Bg;

Mat image = Mat::zeros(720, 1280, CV_8UC3 );

int main(int argc, char* argv[])
{

	VideoCapture capture;
	capture.open(0);
	capture.set(CV_CAP_PROP_FRAME_WIDTH, 1280);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT, 720);

	while (TRUE)
	{
		capture.read(curr_frame);
		alpha.set("nmixtures",3);		
		alpha.operator()(curr_frame, Final, 0.1);
		//alpha.getBackgroundImage(Bg); 
		//Final = curr_frame - ( Bg / 2);
		Mat element = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(7, 7));
		erode(Final,Final, element);
		int x=0,y=0,rows=Final.rows,cols=Final.cols,num=0,sumx=0,sumy=0,pixval=0,x1=0,y1=0;
		for(x=0;x<=rows;x++)
		{
			for(y=0;y<=cols;y++)
			{
				pixval=Final.at<unsigned char>(x,y);
				//printf("%d\n",pixval);
				if(pixval>0)
				{
					sumx=sumx+x;
					sumy=sumy+y;
					//printf("%d\n",num);
					num++;

				}
			}
		}
		printf("%d,%d, %d\n",sumx/num,sumy/num, num);
		vector<vector<Point> > contours;
		vector<Vec4i> hierarchy;
		findContours(Final, contours, hierarchy, 5, 5, Point(0, 0));

		vector<vector<Point> > contours_poly(contours.size());
		vector<Rect> boundRect(contours.size());
		
		vector<Point2f>center(contours.size());
		vector<float>radius(contours.size());

		for (int i = 0; i < contours.size(); i++)
		{
			approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
			boundRect[i] = boundingRect(Mat(contours_poly[i]));
			minEnclosingCircle((Mat)contours_poly[i], center[i], radius[i]);
		}

				for (int i = 0; i< contours.size(); i++)
		{
					Scalar color;
			drawContours(Final, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point());
			rectangle(Final, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0);
			
		}

		imshow("", Final);
		//imshow("",curr_frame);
		//imshow("", Final);
		if(waitKey(30)>=0) break;
	}
	return 0;
}
