/*
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "colordetect.h"

#include <iostream>
#include<stdio.h>


using namespace cv;
//using namespace cv;

void hist(Mat &image)
{
	int r[256], b[256], g[256];

		
		
		int i,j;
		for (i = 0; i < image.rows/4; i++)
		{
			for (j = 0; j < image.cols/4; j++)
			{
				b[(int)image.at<Vec3b>(i, j)[0]]++;
				g[(int)image.at<Vec3b>(i, j)[1]]++;
				r[(int)image.at<Vec3b>(i, j)[2]]++;
			}
		}
		
		for (i = 0; i < image.rows; i++)
		{
			for (j = 0; j < image.cols; j++)
			{
				std::cout<<b[(int)image.at<Vec3b>(i, j)[0]]<<"\n";
				std::cout << g[(int)image.at<Vec3b>(i, j)[1]] << "\n";
				std::cout << r[(int)image.at<Vec3b>(i, j)[2]] << "\n";
			}
		}



}


int main()
{

	Mat image = imread("download.jpg");

	if (image.data)
		std::cout << "Successful";
	else
		std::cout << "Failed";
	namedWindow("Original");
	imshow("Original", image);


	
hist(image);


	waitKey(10000);





}


*/











/*
//laplacian operator
void sharpen(Mat &image2,Mat image)
{

	
	int i = 0;
	int j ;
	for (i=1; i<(image.rows-1); i++)
	{
		uchar* cur = image.ptr<uchar>(i);
		uchar* cur2 = image2.ptr<uchar>(i);
		uchar* prev = image.ptr<uchar>(i - 1);
		uchar* next = image.ptr<uchar>(i + 1);
		for (j = 1; j < (image.cols - 1)*3; j++)
		{
			cur2[j] = 5 * cur[j] - prev[j] - cur[j - 1] - cur[j + 1] - next[j];

		}

	}





}


*/





/*

int main()
{

	Mat image = imread("download.jpg");

	namedWindow("Original");
	imshow("Original", image);

	ColorDetector cdetect;

	cdetect.SetTargetColor(107, 172, 70);
	cdetect.setmindistance(50);
	cdetect.process(image);

	
	

	waitKey(10000);





}*/

/*
//using iterators
void color_reduce(Mat &image, int n)
{
	Mat_<Vec3b>::iterator it = image.begin<Vec3b>();
	Mat_<Vec3b>::iterator itend = image.end<Vec3b>();

	for (; it != itend; it++)
	{
		(*it)[0] = (*it)[0] / n*n + n / 2;
		(*it)[1] = (*it)[1] / n*n + n / 2;
		(*it)[2] = (*it)[2] / n*n + n / 2;
	}

}
*/

// scanning using pointers and color reduce
//color reduce
/*
void color_reduce(Mat &image, int n)
{
	int r = image.rows;
	int c = image.cols*image.channels();
	int i, j;

	int mask = 0xFF << 6;

	for (i = 0; i < r; i++)
	{
		uchar* data = image.ptr<uchar>(i);
		for (j = 0; j < c; j++)
			//data[j] = data[j] / n*n + n / 2;
			data[j] = (data[j] & mask) + n / 2;
	
	}

}


// scanning using pointers and color reduce

int main()
{

	Mat image = imread("download.jpg");

	namedWindow("Original");
	imshow("Original", image);
	

	namedWindow("Modified");

	color_reduce(image, 64);


	imshow("Modified", image);

	waitKey(5000);





}
*/



//accessing pixel values and adding noise
/*
void salt(Mat &image, int n)
{
	int k;
	for (k = 0; k < n; k++)
	{
		int i = rand() % image.rows;
		int j = rand() % image.cols;

		image.at<Vec3b>(i, j)[0] = 255;
		image.at<Vec3b>(i, j)[1] = 255;
		image.at<Vec3b>(i, j)[2] = 255;
	}




}

int main()
{
	Mat image = imread("download.jpg");

	namedWindow("Original");
	imshow("Original", image);

	namedWindow("Modified");

	salt(image, 3000);


		imshow("Modified", image);

	waitKey(5000);
	
	return 1;
}*/