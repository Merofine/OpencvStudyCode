#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
#include <iostream>

using namespace cv;
using namespace std;
using namespace cv::xfeatures2d;

//轨迹条的相关
int minHessian = 100;
int maxHessian = 400;
void CallbackDemo(int, void*);

Mat srcImage = imread("beautiful.jpeg");
char SrcWindowname[] = "Load picture";
char DstWindowname[] = "Surf Picture";

int main(int argc, char** argv)
{
	if (!srcImage.empty())
	{
		cout << "could not find the picture..." << endl;
	}
	else {
		cout << "success to load the picture..." << endl;
	}
	namedWindow(SrcWindowname,WINDOW_AUTOSIZE);
	namedWindow(DstWindowname,WINDOW_AUTOSIZE);
	imshow(SrcWindowname,srcImage);

	//创建滑动条
	createTrackbar("Hessian_value:",DstWindowname,&minHessian,maxHessian,CallbackDemo);
	CallbackDemo(0,0);


	waitKey(0);
	return 0;
}

void CallbackDemo(int, void*)
{
	//检测特征点
	Ptr<SURF> detector = SURF::create(minHessian);//定义SURF中的hessian阈值特征点检测算子
	vector<KeyPoint> keypoint1;
//	Mat detectImage(srcImage.size(),srcImage.type());
	detector->detect(srcImage,keypoint1);

	//绘制特征关键点
	Mat dstImage = Mat(srcImage.size(), srcImage.type());
	Scalar pointcolor(0,0,255);
	drawKeypoints(srcImage,keypoint1,dstImage,pointcolor);

	//显示图像
	imshow(DstWindowname,dstImage);

}