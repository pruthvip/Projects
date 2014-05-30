
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>

using namespace cv;

int main()
{
	Mat image = imread("a.jpg", 2);
	image.convertTo(image, CV_32F);
	Mat noise(image.rows, image.cols, CV_32F);
	float var = 20;
	float R = 40;







	char key = 0;
	while (key != 27)
	{
		key = waitKey(10);
	}
	return 0;




}