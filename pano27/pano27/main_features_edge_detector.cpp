#include"features.h"
#include<iostream>
using namespace cv;

int main()
{
	features morp;
	//morp.setThreshold(20);

	Mat image;
	Mat result;
	image = imread("corner.jpg");
	std::cout << image.elemSize() << "\n";
	result = imread("corner.jpg",2);
	
	std::cout << result.size();
	cvNamedWindow("image");
	namedWindow("edges");
	namedWindow("corners");
	imshow("image", image);

	result=morp.getEdges(image);
	imshow("edges", result);
	result = morp.corners(image);
	imshow("corners", result);
	std::getchar();
	waitKey(500000);
	return 0;
	


}