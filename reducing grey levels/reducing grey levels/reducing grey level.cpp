
#include"Into_8_grey.h"

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>

using namespace cv;


int main()
{
	Mat image = imread("a.jpg");
	Mat grey = BGR_grey(image);

	namedWindow("Original");
	imshow("Original", grey);

	int div=64;
	for (int i = 0; i < grey.rows; i++)
	{
		for (int j = 0; j < grey.cols; j++)
		{
			//std::cout << grey.at<uchar>(i, j);
			grey.at<uchar>(i, j) = grey.at<uchar>(i, j)/div*div +div/2;
		}
	}


	namedWindow("2_levels");
	imshow("2_levels", grey);

	char key = 0;
	while (key != 27)
	{
		key = waitKey(10);
	}

	return 0;


}