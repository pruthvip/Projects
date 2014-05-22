#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>
using namespace cv;

int main()
{
	Mat image = imread("a.jpg", 2);
	
	namedWindow("original");
	imshow("original", image);

	Mat des;
	equalizeHist(image, des);

	namedWindow("Inbuilt");
	imshow("Inbuilt", des);


	float histo[256];
	for (int i = 0; i < 256; i++)
		histo[i] = 0;

	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			histo[(int)(image.at<uchar>(i, j))]++;
		}
	}
	int max = 0;
	for (int i = 0; i < 256; i++)
	{
		std::cout << i << "  " << histo[i] << "\n";
		if (max < histo[i])
			max = histo[i];
	}

	std::cout << "\n\n\n\n" << max << "\n\n\n\n";

	/*
	Mat HistoGraph = Mat::zeros( max+1,256, CV_8UC1);


	//creating the histogram for the original image

	int t = 0;
	for (int j = 0; j <= 255; j++)
	{
		t = histo[j];
		for (int i = max - 1; i >= 0; i--)
		{
			if (t--)
			{
				HistoGraph.at<uchar>(i, j) =0;
			}
		}
	}


	namedWindow("Histogram");
	imshow("Histogram", HistoGraph);*/
	float cdf[256];
	cdf[0] = histo[0];
	for (int i = 1; i < 256; i++)
	{
		cdf[i] = cdf[i - 1] + histo[i];

	}

	int cdf_min = cdf[0];
	int cdf_max = cdf[255];
	float constant = 255.0 / (image.rows*image.cols - cdf_min);
	
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{ 
			image.at<uchar>(i, j) = (int)((cdf[(int)(image.at<uchar>(i, j))] - cdf_min)*constant);
		}
	}

	namedWindow("from_basics");
	imshow("from_basics", image);

	
	char key = 0;
	while (key != 27)
	{
		key = waitKey(10);
	}


	return 0;

}