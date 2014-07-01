#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>
#include<random>
#include<math.h>
#include<cmath>
#include<fstream>

using namespace cv;
using namespace std;


string intToString(int number){

	//this function has a number input and string output
	std::stringstream ss;
	ss << number;
	return ss.str();
}


int main()
{
	string a = "f (";
	string b = ").png";
	unsigned int f = 2;

	//calling the 1st frame
	Mat frame = imread(a + intToString(f) + b);

	imshow("out", frame);
	Rect rec(50, 100, 30, 30);
	rectangle(frame, Point(50, 100), Point(80, 130), Scalar(0, 255, 0),1);
	namedWindow("out");
	imshow("out", frame);
	char xx = getchar();

	return 0;


}