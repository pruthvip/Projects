
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>

using namespace cv;


int main()
{

	Mat image = imread("g.png", 0);
	namedWindow("Real Image");

	moveWindow("Real Image", 0, 0);
	imshow("Real Image", image);

	Mat res= Mat(image.size(), CV_8UC1);

	//GaussianBlur(image,image, Size(11, 11), 0);

	adaptiveThreshold(image,res, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 5, 2);
	 
	namedWindow("after blurring and thresholding");

	moveWindow("after blurring and thresholding", image.cols, 0);
	imshow("after blurring and thresholding", res);

	//bitwise_not(res,res);

	/*

	// might be some broken lines, to fill them dilation is being used
	//Mat kernel = (Mat_<uchar>(3, 3) << 0, 1, 0, 1, 1, 1, 0, 1, 0);
	//dilate(res,res, kernel);

	moveWindow("after inverting", image.cols * 2, 0);
	imshow("after inverting", res);

	int count = 0;
	int max = -1;
	Point maxPt;

	for (int y = 0; y<res.size().height; y++)
	{
		uchar *row = res.ptr(y);
		for (int x = 0; x<res.size().width; x++)
		{
			if (row[x] >= 128)
			{
				int area = floodFill(res, Point(x, y), CV_RGB(0, 0, 64));

				if (area>max)
				{
					maxPt = Point(x, y);
					max = area;
				}
			}
		}
	}

	//floodFill(res, maxPt, CV_RGB(255, 255, 255));
	moveWindow("after inverting and dilation", image.cols * 2, 0);
	imshow("after inverting and dilation", res);
	*/
	char key = 0;
	while (key != 27)
	{
		key = waitKey(10);
	}

	return 0;

}