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
Mat Draw(Mat &src) {
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

int mask[3][3]	= { 0, -1, 0, -1, 4, -1, 0, -1, 0 };	//  Laplacian mask 四鄰域
int mask2[3][3] = { 1, 1, 1, 1, -8, 1, 1, 1, 1 };		//  Laplacian mask 八鄰域

void Laplacian(Mat src, Mat dst);
int main() {
	/*  Cameraman.bmp  */
	string pic	= "Cameraman.bmp";
	Mat src		= imread(pic, 0);
	Mat dst		= imread(pic, 0);
	// 做拉普拉斯銳化
	Laplacian(src, dst);
	// 顯示結果
	showImage(src, Draw(src), "Cameraman_Original");	// 顯示原圖
	showImage(dst, Draw(dst), "Cameraman_Laplacian");	// 顯示銳化結果

	/*  Peppers.bmp  */
	pic = "Peppers.bmp";
	src = imread(pic, 0);
	dst = imread(pic, 0);
	// 做拉普拉斯銳化
	Laplacian(src, dst);
	// 顯示結果
	showImage(src, Draw(src), "Peppers_Original");	// 顯示原圖
	showImage(dst, Draw(dst), "Peppers_Laplacian");	// 顯示銳化結果

	/*  Lena.bmp  */
	pic = "Lena.bmp";
	src = imread(pic, 0);
	dst = imread(pic, 0);
	// 做拉普拉斯銳化
	Laplacian(src, dst);
	// 顯示結果
	showImage(src, Draw(src), "Lena_Original");	// 顯示原圖
	showImage(dst, Draw(dst), "Lena_Laplacian");	// 顯示銳化結果

	waitKey(0);
	return 0;
}

void Laplacian(Mat src, Mat dst)
{
	int c = 1;
	for (int i = 1; i < src.rows - 1; i++)
	{
		for (int j = 1; j < src.cols - 1; j++)
		{
			dst.at<uchar>(i, j) = saturate_cast<uchar>(mask[1][1] * src.at<uchar>(i, j) +
				(mask[0][0] * src.at<uchar>(i - 1, j - 1) + mask[1][0] * src.at<uchar>(i, j - 1) + mask[2][0] * src.at<uchar>(i + 1, j - 1) +
					mask[0][1] * src.at<uchar>(i - 1, j) + mask[2][1] * src.at<uchar>(i + 1, j) +
					mask[0][2] * src.at<uchar>(i - 1, j + 1) + mask[1][2] * src.at<uchar>(i, j + 1) + mask[2][2] * src.at<uchar>(i + 1, j + 1)));
			//將算出來的拉普拉斯與原本值相加存回去
			dst.at<uchar>(i, j) = saturate_cast<uchar>(src.at<uchar>(i, j) + c * dst.at<uchar>(i, j));
		}
	}
}