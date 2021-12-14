#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>                                    
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

void Histogram_Equalization(Mat src, Mat dst);

int main() {
	/*  Peppers.bmp  */
	string pic = "Peppers.bmp";
	Mat src = imread(pic, 0);
	Mat HE = imread(pic, 0);

	Histogram_Equalization(src, HE); // 做直方圖等化
	showImage(src, Draw(src), "Peppers_Original");	// 顯示原圖
	showImage(HE, Draw(HE), "Peppers_Histogram_Equalization"); // Global直方圖等化結果

	/*  Lena.bmp  */
	pic = "Lena.bmp";
	src = imread(pic, 0);
	HE = imread(pic, 0);

	Histogram_Equalization(src, HE); // 做直方圖等化
	showImage(src, Draw(src), "Lena_Original"); // 顯示原圖
	showImage(HE, Draw(HE), "Lena_Histogram_Equalization"); // Global直方圖等化結果

	/*  Cameraman.bmp  */
	pic = "Cameraman.bmp";
	src = imread(pic, 0);
	HE = imread(pic, 0);
	Histogram_Equalization(src, HE); // 做直方圖等化
	showImage(src, Draw(src), "Cameraman_Original"); // 顯示原圖
	showImage(HE, Draw(HE), "Cameraman_Histogram_Equalization"); // Global直方圖等化結果

	waitKey(0);
	return 0;
}
void  Histogram_Equalization(Mat src, Mat dst)
{
	int MN = 65536;
	int L = 256;
	int n[256]; // 灰階值出現次數
	double p[256]; // 出現機率
	double s[256]; // 等化值

	// 初始化陣列
	for (int i = 0; i < 256; i++)
	{
		n[i] = 0;
	}
	// 讀取灰階值數量 n
	uchar* readImage = src.data;
	for (int i = 0; i < src.total(); i++)
	{
		//printf("%u ",p[i] );
		int num = readImage[i];
		n[num]++;
	}
	// 算 p
	for (int i = 0; i < 256; i++)
	{
		p[i] = double(n[i]) / double(MN);
	}
	// 算 s
	int L1 = L - 1;
	s[0] = p[0] * (L - 1);
	for (int i = 1; i < 256; i++)
	{
		s[i] = p[i] * double(L1) + s[i - 1];
	}
	// 四捨五入
	int result[256];
	char tmp[14];
	for (int i = 0; i < 256; i++)
	{
		result[i] = 0;
		sprintf(tmp, "%.0lf", s[i]);
		result[i] = atoi(tmp);
	}
	// 等化結果存回dst
	uchar* writeImage = dst.data;
	for (int i = 0; i < dst.total(); i++)
	{
		int num = writeImage[i];
		writeImage[i] = result[num];
	}
}