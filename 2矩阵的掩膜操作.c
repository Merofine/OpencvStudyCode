#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
#include <stdio.h>

using namespace cv;

int main(int argc, char** argv)
{
	Mat src = imread("liaowenbin.bmp");
	namedWindow("open picture",WINDOW_AUTOSIZE);
	imshow("open picture",src);


	double t = getTickCount();    //***计算时间语句
	Mat kernel = (Mat_<char>(3,3) <<       //定义一个掩膜
		         0,-1,0,
		        -1,5,-1,
		         0,-1,0);	
	Mat dst;
	filter2D(src,dst,src.depth(), kernel);//掩膜操作
	
	double time = (getTickCount()-t) / getTickFrequency();//***
	std::cout << "usetime : " << time << std::endl;//***
	//printf("usetime :%0.2f \n",time);

	namedWindow("Output Picture",WINDOW_AUTOSIZE);
	imshow("Output Picture", dst);

	waitKey(0);
	return 0;
}