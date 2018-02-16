#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	Mat src = imread("liaowenbin.bmp");
	if (src.empty())
	{
		printf("Not file.../n");
		return -1;
	}
	//只会复制对象的头和指针
#if 0
	Mat dst(src);
	namedWindow("Picture",WINDOW_AUTOSIZE);
	imshow("Picture",dst);
#endif

	//完全复制 Mat clone()
#if 0
	Mat dst = src.clone();
	namedWindow("Picture", WINDOW_AUTOSIZE);
	imshow("Picture", dst);
#endif

	//完全复制 void copyTo(Mat Image)

#if 0
	Mat dst;
	src.copyTo(dst);
	namedWindow("Picture", WINDOW_AUTOSIZE);
	imshow("Picture", dst);
#endif

#if 0
	//定义小数组
	Mat dst =(Mat_<uchar>(3, 3) << 0, 5, 6, 
		3,4,5,
		4,2,1);
	cout << "dst = " << dst << endl;

	//单通道的像素指针
	uchar* p = dst.ptr(0); //0表示第1行
	//cout << "*p = " << *(p+1) << endl << endl << "src =" 
	//	<< src << endl;
	printf("*p = %hhd \n",*(p+8));

	system("Pause");
#endif

#if 0
	Mat dst(3,3,CV_8UC3,Scalar(1,23,45));
	cout << "dst = " << dst << endl << endl;
	
	//多通道的像素指针
	uchar* p = dst.ptr(0);
	cout << "p = " << static_cast<const void *>(p) << endl;
	printf("*p = %hhd \n",*(p+5));
	system("Pause");

#endif

	waitKey(0);
	return 0;
}