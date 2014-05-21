#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>

using namespace cv;

class features{

private:
	int threshold1;
	Mat cross;
	Mat diamond;
	Mat square;
	Mat x;

public:

	features() :cross(5, 5, CV_8U, Scalar(0)),
		diamond(5, 5, CV_8U, Scalar(1)),
		square(5, 5, CV_8U, Scalar(1)),
		x(5, 5, CV_8U, Scalar(0)){

		// for cross (plus sign)
		int i;
		for (i = 0; i < 5; i++)
		{
			cross.at<uchar>(2, i)= 1;
			cross.at<uchar>(i,2) = 1;
		}

		diamond.at<uchar>(0, 0) = 0;
		diamond.at<uchar>(0, 1) = 0;
		diamond.at<uchar>(1, 0) = 0;
		diamond.at<uchar>(4, 4) = 0;
		diamond.at<uchar>(3, 4) = 0;
		diamond.at<uchar>(4, 3) = 0;
		diamond.at<uchar>(4, 0) = 0;
		diamond.at<uchar>(4, 1) = 0;
		diamond.at<uchar>(3, 0) = 0;
		diamond.at<uchar>(0, 4) = 0;
		diamond.at<uchar>(0, 3) = 0;
		diamond.at<uchar>(1, 4) = 0;

		for ( i = 0; i<5; i++) {
			x.at<uchar>(i, i) = 1;
			x.at<uchar>(4 - i, i) = 1;
		}
	}

	


	void setThreshold(int a)
	{
		threshold1 = a;
	}

	void applyThreshold(Mat image)
	{
		threshold(image, image, threshold1, 255, CV_THRESH_BINARY);

	}

	Mat getEdges(Mat image)  // edges
	{
		Mat result;
		morphologyEx(image, result, MORPH_GRADIENT, Mat());
		applyThreshold(result);
		return result;


	}


	Mat corners(Mat image)
	{
		Mat result;
		// Dilate with a cross 
		dilate(image, result, cross);
		// Erode with a diamond
		erode(result, result, diamond);
		Mat result2;
		// Dilate with a X 
		dilate(image, result2, x);
		// Erode with a square
		erode(result2, result2, square);
		// Corners are obtained by subtracting 
		// the two closed images
		absdiff(result2, result, result);
		// Apply threshold to obtain a binary image
		applyThreshold(result);
		return result;

	}




};