#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>

using namespace cv;
int main()
{
	VideoCapture cam(0);

	if (cam.isOpened() == false)
	{
		std::cout << "error";
		return 0;
	}

	Mat orig;
	Mat processed;

	std::vector<Vec3f> Vcircles;   // 3 element ;floats;output of hough

	std::vector<Vec3f>::iterator itrCircles;

	namedWindow("original");
	namedWindow("processed");

	char key=0;

	while (key!=27)
	{
		if (cam.read(orig) == NULL)
		{
			std::cout << "Error";
			break;
		}
		
		inRange(orig, Scalar(0, 0, 100), Scalar(100, 100, 256), processed);// find the color

		GaussianBlur(processed, processed, Size(9, 9), 1.5);

		HoughCircles(processed, Vcircles, CV_HOUGH_GRADIENT, 2, processed.rows / 4, 100, 50, 10, 100);

		for (itrCircles = Vcircles.begin(); itrCircles != Vcircles.end(); itrCircles++)
		{
			std::cout << "ball at  x " << (*itrCircles)[0] << "  y =  " << (*itrCircles)[1] << " z =  " << (*itrCircles)[2]
				<< "\n";

			circle(orig, Point((int)(*itrCircles)[0], (int)(*itrCircles)[1]),
				3,
				Scalar(255, 0, 0),
				CV_FILLED);


			circle(orig, Point((int)(*itrCircles)[0], (int)(*itrCircles)[1]),
				(int)(*itrCircles)[2],
				Scalar(0, 0, 255), 3);
		}//for end

			imshow("original", orig);
			imshow("processed", processed);

			key = waitKey(10);


		}//while


	return 0;

	}




	




