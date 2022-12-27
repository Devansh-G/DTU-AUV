#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/////////////////////////////////////////////					Finding Mid point						/////////////////////////////////////////////

Mat imgHSV, mask;
int hmin = 0, smin = 94, vmin = 0;
int hmax = 160, smax = 255, vmax = 97;
float x, y;

void getContours(Mat mask, Mat img)
{
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(mask, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	for (int i = 0; i < contours.size(); i++)
	{
		int area = contourArea(contours[i]);

		vector<vector<Point>> conPoly(contours.size());
		vector<Rect> boundRect(contours.size());

		if (area > 1000)
		{
			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
			
			boundRect[i] = boundingRect(conPoly[i]);
			//rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 2);
			x = (boundRect[i].tl().x + boundRect[i].br().x)/2;
			y = (boundRect[i].tl().y + boundRect[i].br().y) / 2;
		}
	}
	circle(img, Point(x, y), 2,Scalar(0,255,0),3);

}

void main()
{
	string path = "Resources/pract.jpg";
	Mat img = imread(path);
	cvtColor(img, imgHSV, COLOR_BGR2HSV);

	
		Scalar lower(hmin, smin, vmin);
		Scalar upper(hmax, smax, vmax);
		inRange(imgHSV, lower, upper, mask);
		
			getContours(mask, img);

			imshow("Image", img);
			//imshow("Image mask", mask);
			waitKey(0);
}