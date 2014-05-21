
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
//#include "fs.cpp"
#include"SIFT1.h"

//void match(Mat image1, Mat image2);
#include<iostream>
#include<stdio.h>
#include<conio.h>
using namespace cv;
using namespace std;
int main()
{

	cout << "hello";
	Mat image1 = imread("2.jpg");
	//Mat image2 = imread("1.jpg");
	//cout << image.channels() << endl;
	SIFT1 controller1(image1);


	controller1.DoSIFT();	
//	controller1.match(image1, image2);
	//controller1.match(image1, image2);
	waitKey(100000);
	
}