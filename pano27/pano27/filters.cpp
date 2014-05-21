/*#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>


using namespace cv;

int main()
{

	Mat image = imread("download.jpg");
	namedWindow("Image");
	//namedWindow("Diluted");
	//namedWindow("eroded");
	//namedWindow("closed");
	Mat eroded, dil;
	//erode(image, eroded, Mat());
	//dilate(image, dil, Mat());
	imshow("Image", image);
	//imshow("Diluted", dil);
	//imshow("eroded", eroded);
	cv::Mat element5(5, 5, CV_8U, cv::Scalar(1));
	cv::Mat closed;
	cv::morphologyEx(image, closed, cv::MORPH_CLOSE, element5);
	cv::morphologyEx(closed,closed, cv::MORPH_OPEN, element5);
	//How it works...
//	imshow("closed", closed);
	waitKey(500000);

	return 0;

}*/