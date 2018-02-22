#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Mat src = imread("liaowenbin.jpg");
	if (!src.data)
	{
		printf("could not find picture .../n");
		return -1;
	}
	char WINDOWNAME_SRC[] = "Src";
	char WINDOWNAME_BLUR[] = "blur";
	char WINDOWNAME_Gauss[] = "Gaussblur";
	char WINDOWNAME_DoubleGauss[] = "DoubleGaussBlur";
	char WINDOWNAME_Result[] = "ResultImg";
	namedWindow(WINDOWNAME_SRC,WINDOW_AUTOSIZE);
	//namedWindow(WINDOWNAME_BLUR,WINDOW_AUTOSIZE);
	//namedWindow(WINDOWNAME_Gauss, WINDOW_AUTOSIZE);
	namedWindow(WINDOWNAME_DoubleGauss, WINDOW_AUTOSIZE);
	namedWindow(WINDOWNAME_Result,WINDOW_AUTOSIZE);


	//高斯双边滤波
	Mat DoubleGaussDst = Mat(src.size(), src.type());
	bilateralFilter(src,DoubleGaussDst,3,1,1);

	//提高对比度
	Mat resultImg = Mat(src.size(), src.type());
	Mat kernel = (Mat_<char>(3,3)<<0,-1,0,
		-1,5,-1,
		0,-1,0);
	filter2D(DoubleGaussDst,resultImg,-1,kernel);

	imshow(WINDOWNAME_SRC, src);
	//imshow(WINDOWNAME_BLUR,BlurDst);
	//imshow(WINDOWNAME_Gauss, GaussDst);
	imshow(WINDOWNAME_DoubleGauss, DoubleGaussDst);
	imshow(WINDOWNAME_Result, resultImg);
	waitKey(0);
	return 0;
}