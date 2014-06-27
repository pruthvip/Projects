
#include<opencv2\core\core.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\highgui\highgui.hpp>

#include<stdio.h>
#include<iostream>
#include<random>

using namespace cv;
using namespace std;



const int N = 50;// no of particles

string intToString(int number){

	//this function has a number input and string output
	std::stringstream ss;
	ss << number;
	return ss.str();
}



int main()
{
	// file names are - f ([2-449]).png
	char a[10] = "f (";
	char b[10] = ").png";
	int f = 2;
	
	Mat frame;
	frame = imread(a + intToString(f) + b);
	namedWindow("Out");


	//locating the car manually
	Rect car(175, 210, 42, 31);
	
	
	//making a rectangle around the car
	rectangle(frame, car, Scalar(0, 0,255), 1, 8, 0);
	


	//getting tht height and width of the frame
	const int FRAME_HEIGHT = frame.rows;
	const int FRAME_WIDTH = frame.cols;


	//Particle filter initialization

	Mat Init = (Mat_<float>(6, 1) << car.x, car.y, 0, 0,42,31);


	//for a gaussian noise distribution
	std::default_random_engine generator;
	std::normal_distribution<double> distribution(0, 15);


	//Initializing the particles
	//std::vector<cv::Mat> particle(N, cv::Mat(4, 1, CV_32F));
	Mat particle[N];


	cout << car.x << " " << car.y << "\n";

	for (int i = 0; i < N; i++)
	{
		particle[i] = (Mat_<float>(6, 1) << 0, 0, 0, 0,42,31);
		particle[i].at<float>(0, 0) = Init.at<float>(0, 0) + distribution(generator);
		particle[i].at<float>(1, 0) = Init.at<float>(1, 0) + distribution(generator);
		
		
	}

	for (int i = 0; i < N; i++)
	{
		cout << particle[i] << "\n";
		int x = particle[i].at<float>(0, 0);
		int y = particle[i].at<float>(1, 0);
		int w = particle[i].at<float>(4, 0);
		int h = particle[i].at<float>(5, 0);

		rectangle(frame, Rect(x, y, w,h), Scalar(0, 255, 0), 1, 8, 0);

		imshow("Out", frame);
	
	}

	imshow("Out", frame);

	//press esc to play the video
	waitKey();


	/*

	Rect PF_car = car;


	//Video Starts here

	while (f <= 200)
	{
		 frame= imread(a+intToString(f)+b);
		 f = f + 1;
		 rectangle(frame, PF_car, Scalar(0, 255, 0), 1, 8, 0);
		imshow("Out", frame);
		waitKey(10);

	}



	waitKey();


	*/


	return 0;
}