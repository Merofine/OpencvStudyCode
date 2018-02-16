#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Mat src = imread("liaowenbin.bmp");
	namedWindow("original_pic", WINDOW_AUTOSIZE);
	imshow("original_pic", src);

	//证明完全复制的独立性
#if 1
	Mat allCopy = src.clone();
#else
	Mat allCopy;
	src.copyTo(allCopy);
#endif
	int sun_channel = allCopy.rows * allCopy.cols 
		                          * allCopy.channels();
	uchar* p_point = allCopy.ptr(0);
	for (int channel = 0; channel < sun_channel; channel++)
	{
		*(p_point + channel) = 0;
	}

	namedWindow("src.copyTo",WINDOW_AUTOSIZE);
	imshow("src.copyTo",allCopy);

	//cvtColor转灰度图像
	Mat dst;
	cvtColor(src,dst,CV_BGR2GRAY);
	namedWindow("GRAY",WINDOW_AUTOSIZE);
	imshow("GRAY", dst);


	//cvtColor不可逆
#if 0
	Mat A;
	cvtColor(dst, A, CV_GRAY2BGR);
	namedWindow("Output_RGB", WINDOW_AUTOSIZE);
	imshow("Output_RGB", A);
#endif

	int height = dst.rows;//行数
	int weight = dst.cols;//列数

	cout << "height = " << height << endl;
	cout << "weight = " << weight << endl;
	cout << "depth  = " << dst.depth() << endl;
	
	//用 at<>()函数 处理单通道
	//Point pnt;
	for(int rows = 0;rows < height;rows++)
		for (int cols = 0;cols <weight;cols++)
		{
			int sca = dst.at<uchar>(rows,cols);
			dst.at<uchar>(rows, cols) = 255 - sca;//反转
		}
	namedWindow("GRAY_channe1_turn",WINDOW_AUTOSIZE);
	imshow("GRAY_channe1_turn",dst);

	
	//用 at<>()函数 处理多通道	
	Mat A(src);
	for (int rows = 0; rows < height; rows++)
		for (int cols = 0; cols <weight; cols++)
		{
			int b = A.at<Vec3b>(rows, cols)[0];
			int g = A.at<Vec3b>(rows, cols)[1];
			int r = A.at<Vec3b>(rows, cols)[2];
			A.at<Vec3b>(rows, cols)[0] = 255 - b;//反转
			A.at<Vec3b>(rows, cols)[1] = 255 - g;
			A.at<Vec3b>(rows, cols)[2] = 255 - r;
		}
	namedWindow("RGB_channel3_turn", WINDOW_AUTOSIZE);
	imshow("RGB_channel3_turn", A);

	//证明了单纯复制对象的头和指针部分时，不会复制数据部分，
	//但是通过操作新的对象时，会影响到我们的旧的对象。
	namedWindow("A(src)",WINDOW_AUTOSIZE);
	imshow("A(src)", src);

	/****************/
	//构造函数创建一个Mat类
#if 1
	Mat src2(src.size(), src.type(), Scalar(0, 0, 255));//src2只是跟src一样的大小，一样的格式
	//或者不赋值像素值-->Mat src2(src.size(), src.type());
	namedWindow("Mat src2(src.size(), src.type())",WINDOW_AUTOSIZE);
	imshow("Mat src2(src.size(), src.type())",src2);
#elif 0
	Mat src2;
	src2 = Mat(src.size(), src.type(), Scalar(0, 0, 255));
	//或者不赋值像素值-->src2 = Mat(src.size(), src.type());
	namedWindow("src2 = Mat(src.size(), src.type());", WINDOW_AUTOSIZE);
	imshow("src2 = Mat(src.size(), src.type());", src2);
#elif 0
	Mat src2;
	src2.create(src.size(), src.type());
	src2 = Scalar(0,0,255);
	namedWindow("src2.create(src.size(), src.type());", WINDOW_AUTOSIZE);
	imshow("src2.create(src.size(), src.type());", src2);
#endif
	//将src图像反转回来
	Mat savesrc(src);
	for (int rows = 0; rows < height; rows++)
		for (int cols = 0; cols <weight; cols++)
		{
			int b = savesrc.at<Vec3b>(rows, cols)[0];
			int g = savesrc.at<Vec3b>(rows, cols)[1];
			int r = savesrc.at<Vec3b>(rows, cols)[2];
			savesrc.at<Vec3b>(rows, cols)[0] = 255 - b;//反转
			savesrc.at<Vec3b>(rows, cols)[1] = 255 - g;
			savesrc.at<Vec3b>(rows, cols)[2] = 255 - r;
		}
	namedWindow("Mat savesrc(src);", WINDOW_AUTOSIZE);
	imshow("Mat savesrc(src);", savesrc);


	//另一种将RGB图像转化为GRAY图像
	Mat GraySrc(src.size(), CV_8UC1);
	for (int rows = 0; rows < height; rows++)
		for (int cols = 0; cols <weight; cols++)
		{
			int b = src.at<Vec3b>(rows, cols)[0];
			int g = src.at<Vec3b>(rows, cols)[1];
			int r = src.at<Vec3b>(rows, cols)[2];
			GraySrc.at<uchar>(rows, cols) = max(r,max(b,g));
			//GraySrc.at<uchar>(rows, cols) = min(r, min(b, g));
		}
	namedWindow("GraySrc.at<uchar>(rows, cols) = max(r,max(b,g));", WINDOW_AUTOSIZE);
	imshow("GraySrc.at<uchar>(rows, cols) = max(r,max(b,g));", GraySrc);

	//eye 
	Mat eyeeye = Mat::eye(3,3,CV_8UC1);
	//eyeeye = Scalar(0);
	cout << "eyeeye = " << eyeeye << endl;
	//system("Pause");  opencv3用这个的话，imshow不了图片

	waitKey(0);
	return 0;
}