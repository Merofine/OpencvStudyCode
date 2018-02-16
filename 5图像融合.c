#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	Mat src1 = imread("liaowenbin.bmp");
	Mat src2 = imread("liujiahui.bmp");
	if (!src1.data)
	{
		printf("could not load liaowenbin.bmp .../n");
		return -1;
	}
	if (!src2.data)
	{
		printf("could not load liujiahui.bmp .../n");
		return -1;
	}
	namedWindow("liaowenbin",WINDOW_AUTOSIZE);
	imshow("liaowenbin", src1);
	namedWindow("liujiahui",WINDOW_AUTOSIZE);
	imshow("liujiahui",src2);

	Mat dst;
	cv::addWeighted(
		src1,
		0.5,
		src2,
		1.0-0.5,
		0.0,
		dst,
		-1  //可以不填写
	);
	namedWindow("blend",WINDOW_AUTOSIZE);
	imshow("blend",dst);


	waitKey(0);
	return 0;
}