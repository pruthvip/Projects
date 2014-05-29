
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>

using namespace cv;


void canny(cv::Mat& img ) {
	// Convert to gray
	if (img.channels() == 3)
		cv::cvtColor(img, img, CV_BGR2GRAY);
	// Compute Canny edges
	cv::Canny(img,img, 100, 200);
	// Invert the image
	cv::threshold(img,img, 128, 255, cv::THRESH_BINARY_INV);
}
int main()
{
	Mat frame;
	VideoCapture capture("bike.avi");

	double rate = capture.get(CV_CAP_PROP_FPS);
	std::cout << rate;

	Mat canny_edge;
	bool stop(false);
	namedWindow("Extracted Frame");
	namedWindow("Canny edge");
	
	int delay = 1000/ rate;// delay in millisecond,,,, 1 sec =1000 millisecond
	std::cout << "\n\n" << delay;
	while (!stop)
	{
		if (!capture.read(frame))
			break;
		capture >> canny_edge;
		canny(canny_edge);
		imshow("Extracted Frame", frame);
		imshow("Canny edge", canny_edge);

		if (waitKey(delay) > 0)
			stop = true;

	}

	capture.release();

	char key = 0;
	while (key != 27)
	{
		key = waitKey(10);
	}

	return 0;

}