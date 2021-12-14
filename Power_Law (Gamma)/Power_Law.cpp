#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>                   
#include <math.h>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

// 將兩張圖像放在同一視窗
void showImage(Mat src1, Mat src2, String s)
{
	// 建立新圖像
	int w = src1.cols + src2.cols;
	int h = src1.rows;
	Mat MergeImage = Mat::zeros(Size(w, h), src1.type());
	// 建立圖像ROI
	Rect r1(0, 0, src1.cols, src1.rows);
	Rect r2(0, 0, src2.cols, src2.rows);
	r2.x = src1.cols;
	// 複製內容
	src1.copyTo(MergeImage(r1));
	src2.copyTo(MergeImage(r2));
	imshow(s, MergeImage);
}
// 畫直方圖
Mat Draw(Mat &src)
{
	Mat hist;
	int size = 256;
	float range[] = { 0, 256 }; //範圍 0-255
	const float* Range = { range };
	// 計算圖像的直方圖
	calcHist(&src, 1, 0, Mat(), hist, 1, &size, &Range);
	// 0為黑色 255白色
	Mat final_pic(256, 256, CV_8U, Scalar(255));
	float maxValue = 0;
	// 找maxValue
	for (int i = 0; i < 256; i++) {
		if (hist.at<float>(i) > maxValue)
			maxValue = hist.at<float>(i);
	}
	for (int i = 0; i < 256; i++) {
		int realV = static_cast<int>(hist.at<float>(i) * 10 * 256 / maxValue);
		line(final_pic, Point(i, 255), Point(i, 255 - realV), Scalar(0));
	}
	return final_pic;
}

void Power_Law(Mat src, Mat dst, double Y);
int main() 
{
	/*  Cameraman.bmp  */
	double Y	= 0.5; // 輸入Gamma值
	string pic	= "Cameraman.bmp";
	Mat src = imread(pic, -1);
	Mat pl	= imread(pic, -1);
	// 乘冪律轉換
	Power_Law(src, pl, Y);
	// 顯示結果
	showImage(src, Draw(src), "Cameraman_Original");		// 顯示原圖
	showImage(pl, Draw(pl), "Cameraman_Power_Law  Y=0.5");	// 顯示Power_Law結果

	/*  Peppers.bmp  */
	Y	= 3.5; // 輸入Gamma值
	pic = "Peppers.bmp";
	src = imread(pic, -1);
	pl	= imread(pic, -1);
	// 乘冪律轉換
	Power_Law(src, pl, Y);
	// 顯示結果
	showImage(src, Draw(src), "Peppers_Original");			// 顯示原圖
	showImage(pl, Draw(pl), "Peppers_Power_Law  Y=3.5");	// 顯示Power_Law結果

	/*  Lena.bmp  */
	Y	= 0.4; // 輸入Gamma值
	pic = "Lena.bmp";
	src = imread(pic, -1);
	pl	= imread(pic, -1);
	// 乘冪律轉換
	Power_Law(src, pl, Y);
	// 顯示結果
	showImage(src, Draw(src), "Lena_Original");			// 顯示原圖
	showImage(pl, Draw(pl), "Lena_Power_Law  Y=0.4");	// 顯示Power_Law結果

	waitKey(0);
	return 0;
}

void Power_Law(Mat src, Mat dst, double Y)
{
	//讀取Mat
	uchar* readImage	= src.data;
	uchar* writeImage	= dst.data;
	double c; //常數 將轉換後影像調整回0~255
	c = 255 / (pow(255, Y));
	for (int i = 0; i < src.total(); i++)
	{
		int r = readImage[i];
		int s = c * pow(r, Y);
		writeImage[i] = s;
	}
}