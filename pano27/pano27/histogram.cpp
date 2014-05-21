/*#include "Histogram1d.h"
#include<iostream>

int main()
{
	Mat image = imread("download.jpg");
	Mat image2;
	cvtColor(image, image2, CV_BGR2GRAY);
	Histogram1d h;

	namedWindow("pic", 1);
	MatND histo = h.getHistogram(image2);
	threshold(image2, image2, 83, 255, cv::THRESH_BINARY);
	imshow("pic", image2);

	

	int i;

	for (i = 0; i < 256; i++)
		cout << "Value" << i << " == " << histo.at<float>(i) << endl;
	while (1)
	{

		int iKey = waitKey(50);

		//if user press 'ESC' key
		if (iKey == 27)
		{
			break;
		}
	}


}*/