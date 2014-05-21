
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main()
{
	Mat image = imread("a.jpg", 2);
	int zooimng_factor = 2;
	Mat zoomed = Mat::zeros(image.rows * zooimng_factor, image.cols * zooimng_factor, CV_8UC1);
	int p, q;
	p = 0;
	q = 0;

	//Zoomed_Pixel_replication
	for (int i = 0; i < image.rows; i++)
	{
		q = 0;

		for (int j = 0; j < image.cols; j++)
		{
			zoomed.at<uchar>(p, q) = image.at<uchar>(i, j);
			zoomed.at<uchar>(p + 1, q + 1) = image.at<uchar>(i, j);
			q = q + zooimng_factor;
		}
		p = p + zooimng_factor;
			
	}

	namedWindow("original");
	namedWindow("Zoomed_Pixel_replication");

	imshow("original", image);
	imshow("Zoomed_Pixel_replication", zoomed);


	//zero order hold


	
	char key=0;
	while (key != 27)
	{
		key = waitKey(10);
	}



}