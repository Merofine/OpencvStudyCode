#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

int main()
{
	Mat src = imread("liaowenbin.bmp");
	if (src.empty())
	{
		printf("could not load image...\n");
		return - 1;
	}
	
	//namedWindow和imshow相随相伴,永不分离
	namedWindow("test opencv setup",CV_WINDOW_AUTOSIZE);
	imshow("test opencv setup",src);

	namedWindow("output window",CV_WINDOW_AUTOSIZE);
	Mat output_image;
	
	//颜色空间转换
	cvtColor(src,output_image,COLOR_BGR2HLS);
    imshow("output window",output_image);
	imwrite("output_image.bmp",output_image);
	
	waitKey(0);
	return 0;
}