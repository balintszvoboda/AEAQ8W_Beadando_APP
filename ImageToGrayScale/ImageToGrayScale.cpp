
#include <iostream>
#include "opencv2/opencv.hpp";

#include "../AEAQ8W_Beadando_APP/kernel.h";
#include "kernel.h"

using namespace cv;

uchar** GetRGBChanels(const Mat& source)
{
	int arraySize = source.rows * source.cols;

	unsigned char* R = (unsigned char*)malloc(arraySize * sizeof(unsigned char));
	unsigned char* G = (unsigned char*)malloc(arraySize * sizeof(unsigned char));
	unsigned char* B = (unsigned char*)malloc(arraySize * sizeof(unsigned char));


	for (size_t y = 0; y < source.rows; y++)
	{
		for (size_t x = 0; x < source.cols; x++)
		{
			B[y * source.rows + x] = source.at<Vec3b>(y, x)[0];
			G[y * source.rows + x] = source.at<Vec3b>(y, x)[1];
			R[y * source.rows + x] = source.at<Vec3b>(y, x)[2];
		}
	}

	unsigned char** RGB = (unsigned char**)malloc(3 * sizeof(unsigned char*));
	RGB[0] = R;
	RGB[1] = G;
	RGB[2] = B;

	return RGB;
}

int main()
{
	Mat picture = imread("test_image.jpg", IMREAD_ANYCOLOR);
	imshow("source", picture);
	//waitKey();
	printf("Picture loaded!\n");

	uchar** source = GetRGBChanels(picture);
	printf("Picture converted!\n");

	unsigned char* R = source[2];
	unsigned char* G = source[1];
	unsigned char* B = source[0];

	unsigned char* OUT;
	OUT = (unsigned char*)malloc(picture.cols * picture.rows);

	rgba_to_greyscale_cpp(R, G, B, OUT, picture.rows, picture.cols);
	printf("Picture processed!\n\n");

	/*for (size_t i = 0; i < 50; i++)
	{
		printf("%d;%d;%d -> %d \n", R[i], G[i], B[i], OUT[i]);
	}*/

	Mat my_mat(picture.rows, picture.cols, CV_8UC1, OUT);
	//Mat my_mat(picture.cols, picture.rows, CV_8UC1, OUT);

	imshow("result", my_mat);
	waitKey();

	return 0;
}
