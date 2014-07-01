#include <opencv\cv.h>
#include <opencv\highgui.h>


#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>

using namespace cv;

using namespace std;


int main()
{

	Mat image = imread("a.jpg");
	namedWindow("image");
	imshow("image", image);
	cout << image.size()<<"  "<<image.depth();
	cout << image.depth();
	//cout << image.elemSize();
	cvtColor(image, image, CV_BGR2Lab);

	namedWindow("i2");
	imshow("i2", image);


	waitKey();
	return 0;







}