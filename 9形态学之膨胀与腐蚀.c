#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void CallBack_Demo_Erode(int, void*);
void CallBack_Demo_Dilate(int, void*);
//全局变量
Mat src = imread("helloworld.png");
Mat DilatePic = Mat(src.size(), src.type());
int dilateval = 1;
int dilatecst = 20; 
Mat ErodePic = Mat(src.size(), src.type());
int erodeval = 1;
int erodecst = 20;

int main(int argc, char** argv)
{
	if (!src.data)
	{
		printf("could not find picture .../n");
		return -1;
	}
	namedWindow("原图像",WINDOW_AUTOSIZE);
	namedWindow("膨胀后",WINDOW_AUTOSIZE);
	createTrackbar("dilate-size:", "膨胀后",&dilateval, dilatecst,CallBack_Demo_Dilate);
	namedWindow("腐蚀后",WINDOW_AUTOSIZE);
	createTrackbar("erode-size:", "腐蚀后",&erodeval,erodecst,CallBack_Demo_Erode);
	
	//这个只是让回调函数执行一次把图像显示出来而已，可以不要。
	CallBack_Demo_Dilate(0, 0);
	CallBack_Demo_Erode(0, 0);

	imshow("原图像", src);


	waitKey(0);
	return 0;
}

void CallBack_Demo_Dilate(int, void*)
{
	//获取自定义核
	Size ksize(dilateval, dilateval);
	Mat element = getStructuringElement(MORPH_RECT, ksize);
	//膨胀	
	dilate(src, DilatePic, element);

	imshow("膨胀后", DilatePic);
}

void CallBack_Demo_Erode(int, void*)
{
	//获取自定义核
	Size ksize(erodeval, erodeval);
	Mat element = getStructuringElement(MORPH_RECT, ksize);
	//腐蚀
	erode(src, ErodePic, element);

	imshow("腐蚀后", ErodePic);
}