#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<math.h>

#include<iostream>
using namespace cv;

int main()
{
	Mat image = imread("a.jpg", 2);
	Mat log_image = image.clone();
	namedWindow("original");
	imshow("original", image);

	//inversion
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			image.at<uchar>(i, j) = 255 - image.at<uchar>(i, j);
		}
	}

	namedWindow("Inversed");
	imshow("Inversed", image);
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			log_image.at<uchar>(i, j) = 1*log(log_image.at<uchar>(i, j)+1);
		}
	}

	namedWindow("Log_image");
	imshow("Log_image", log_image);


	char key = 0;
	while (key != 27)
	{
		key = waitKey(10);
	}
	return 0;

}