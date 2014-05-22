

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>

using namespace cv;

Mat BGR_grey(Mat image)
{

	
	

	Mat grey = Mat::zeros(image.rows, image.cols, CV_8UC1);
	Mat Weighted_grey = Mat::zeros(image.rows, image.cols, CV_8UC1);

	 
	for (int i = 0; i < image.rows; i++)
	{
		 
		for (int j = 0; j < image.cols; j++)
		{
			grey.at<uchar>(i, j) = (image.at<Vec3b>(i, j)[0] + image.at<Vec3b>(i, j)[1] + image.at<Vec3b>(i, j)[2]) / 3;
			Weighted_grey.at<uchar>(i, j) = (image.at<Vec3b>(i, j)[0] * 0.11 + image.at<Vec3b>(i, j)[1] * 0.59 + image.at<Vec3b>(i, j)[2] * 0.3);
		}
	}
	 
	return Weighted_grey;
 

 




}