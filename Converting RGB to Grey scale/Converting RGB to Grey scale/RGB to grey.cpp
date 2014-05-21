
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>

using namespace cv;

int main()
{

	Mat image = imread("a.jpg");
	namedWindow("Original");
	namedWindow("Average Grey");

	namedWindow("Weighted-grey");

	imshow("Original", image);
	std::cout << "hello\n";
	 

	Mat grey = Mat::zeros(image.rows, image.cols, CV_8UC1);
	Mat Weighted_grey = Mat::zeros(image.rows, image.cols, CV_8UC1);
	 
	std::cout << "hello\n";
	for (int i = 0; i < image.rows; i++)
	{
		std::cout << "hello\n";
		for (int j = 0; j < image.cols; j++)
		{
			grey.at<uchar>(i, j) = (image.at<Vec3b>(i, j)[0] + image.at<Vec3b>(i, j)[1] + image.at<Vec3b>(i, j)[2])/3;
			Weighted_grey.at<uchar>(i, j) = (image.at<Vec3b>(i, j)[0]*0.11 + image.at<Vec3b>(i, j)[1]*0.59 + image.at<Vec3b>(i, j)[2]*0.3);
		}
	}
	std::cout << "hello\n";
	imshow("Grey", grey);
	imshow("Weighted-grey", Weighted_grey);
	std::cout << "hello\n";
	 
	char key = 0;
	while (key != 27)
	{
		key = waitKey(10);
	}
	return 0;




}