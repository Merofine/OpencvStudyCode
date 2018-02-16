#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
char WindowName[] = "Black-Board";
void DrawLine(Mat& Image);
void DrawRect(Mat& Image);
void DrawEillpse(Mat& Image);
void DrawCricle(Mat& Image);
void DrawPoly(Mat& Image);
void DrawRandomColorText(Mat& Image, char text[]);

int main(int argc, char** argv)
{

	Mat blackboard = Mat::zeros(400,400,CV_8UC3);
	DrawLine(blackboard);
	DrawRect(blackboard);
	DrawEillpse(blackboard);
	DrawCricle(blackboard);
	DrawPoly(blackboard);
	DrawRandomColorText(blackboard,"HelloOpencv");
	waitKey(0);
	return 0;
}

void DrawLine(Mat& Image)
{
	Point a, b;
	a.x = 0;
	a.y = 0;
	b.x = 400;
	b.y = 400;
	Scalar color(255,0,0);
	line(Image,a,b,color,2);
}

void DrawRect(Mat& Image)
{
	Point a = Point(Image.cols/4,Image.rows/4);
	Point b = Point(Image.cols*3/4,Image.rows*3/4);
	Rect rect(a,b);
	Scalar color = Scalar(0,255,0);
	rectangle(Image,rect,color,2);
}

void DrawEillpse(Mat& Image)
{
	Point cen(Image.cols / 2, Image.rows / 2);
	Size len = Size(100,200);
	Scalar color(0,0,255);
	ellipse(Image,cen,len,90,0,360,color);
}

void DrawCricle(Mat& Image)
{
	Point cen = Point(Image.cols/2,Image.rows/2);
	Scalar color(255, 255, 255);
	int radius = 200;
	circle(Image,cen,radius,color,2);
}

void DrawPoly(Mat& Image)
{
	Point pts[1][4];
	pts[0][0] = Point(50,50);
	pts[0][1] = Point(150, 100);
	pts[0][2] = Point(200, 400);
	pts[0][3] = Point(50,50);
	const Point* p[] = {pts[0]};
	const int nps[] = { 4 };
	Scalar color(255, 255, 255);
	fillPoly(Image,p,nps,1,color);
}

void DrawRandomColorText(Mat& Image,char text[])
{
	RNG rng;
	Scalar color;
	Point p_text(Image.cols / 4, Image.rows/2);
	namedWindow(WindowName, WINDOW_AUTOSIZE);
	while(1)
	{
		color = Scalar(rng.uniform(0,255), rng.uniform(0, 255), rng.uniform(0, 255));
		putText(Image, text, p_text,CV_FONT_BLACK,2.0,color,2);
		imshow(WindowName,Image);
		waitKey(200);
	}
}