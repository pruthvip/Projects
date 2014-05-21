#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>


using namespace cv;


int main()
{

	Mat image = imread("a.jpg", 2);

	Mat eroded;

	erode(image, eroded, Mat());

	namedWindow("Eroded Image");
	imshow("Eroded Image", eroded);
	// Dilate the image
	Mat dilated; // the destination image
	dilate(image, dilated, Mat());
	// Display the dilated image
	namedWindow("Dilated Image");
	imshow("Dilated Image", dilated);

	char key = 0;
	while (key != 27)
	{
		key = waitKey(10);
	}


	return 0;


}