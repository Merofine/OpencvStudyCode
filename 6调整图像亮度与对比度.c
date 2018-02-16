#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

#define alpha 1.5
#define date  10

int main(int argc, char** argv)
{
	Mat src1 = imread("liaowenbin.bmp");
	if (!src1.data)
	{
		printf("could not load liaowenbin.bmp .../n");
		return -1;
	}
	namedWindow("liaowenbin",WINDOW_AUTOSIZE);
	imshow("liaowenbin", src1);

	Mat srczero = Mat::zeros(src1.size(), src1.type());
	int height = src1.rows;
	int width = src1.cols;
	
	for(int row = 0;row < height;row++)
		for (int col = 0; col < width; col++)
		{
			uchar b = src1.at<Vec3b>(row,col)[0];
			uchar g = src1.at<Vec3b>(row,col)[1];
			uchar r = src1.at<Vec3b>(row,col)[2];

			srczero.at<Vec3b>(row,col)[0] = saturate_cast<uchar>(alpha*b + date);
			srczero.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(alpha*g + date);
			srczero.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(alpha*r + date);
		}
	namedWindow("Output",WINDOW_AUTOSIZE);
	imshow("Output",srczero);


	waitKey(0);
	return 0;
}