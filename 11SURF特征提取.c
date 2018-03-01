#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
#include <iostream>

using namespace cv;
using namespace std;
using namespace cv::xfeatures2d;

//轨迹条的相关
int minHessian = 100;
int maxHessian = 8000;
void CallbackDemo(int, void*);

Mat srcImage1 = imread("Cap1.bmp");
Mat srcImage2 = imread("Cap2.bmp");
char Pic1WindowName[] = "Pic1";
char Pic2WindowName[] = "Pic2";
char DstWindowname[] = "BruteForcePicture";

int main(int argc, char** argv)
{
	if (!srcImage1.empty() || !srcImage2.empty())
	{
		cout << "success to load the picture..." << endl;
	}
	else {
		cout << "could not find the picture..." << endl;
	}
	namedWindow(Pic1WindowName,WINDOW_AUTOSIZE);
	imshow(Pic1WindowName,srcImage1);
	namedWindow(Pic2WindowName,WINDOW_AUTOSIZE);
	imshow(Pic2WindowName,srcImage2);
	namedWindow(DstWindowname,WINDOW_AUTOSIZE);

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
	detector->detect(srcImage1,keypoint1);
	vector<KeyPoint> keypoint2;
	detector->detect(srcImage2, keypoint2);
	
	//计算特征描述子(特征向量)
	Ptr<SurfDescriptorExtractor> extractor = SURF::create();
	Mat descripte1,
		descripte2;
	extractor->compute(srcImage1,keypoint1,descripte1);
	extractor->compute(srcImage2,keypoint2,descripte2);

	//根据描述子，用BruteForce进行匹配
	Ptr<DescriptorMatcher> matchertor = DescriptorMatcher::create("BruteForce");    //实例化一个匹配器
	vector<DMatch> matches;
	matchertor->match(descripte1,descripte2,matches);

	//绘制关键点的匹配
	Mat DstImage;
	drawMatches(srcImage1,keypoint1,srcImage2,keypoint2,matches,DstImage);

	//显示图像
	imshow(DstWindowname,DstImage);

}