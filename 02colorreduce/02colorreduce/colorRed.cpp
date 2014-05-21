#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>


using namespace cv;

void colorReduce(Mat image,int div)
{
	int rows = image.rows;
	int cols = image.cols*image.channels();

	int i, j;
	for (i = 0; i < rows; i++)
	{
		uchar* data = image.ptr<uchar>(i);

		for (j = 0; j < cols; j++)
			data[j] = data[j] / div *div + div / 2;
	}

	return;
}


int main()
{
	Mat image = imread("a.jpg");

	Mat Dup = image.clone();
	
	colorReduce(Dup,128);

	namedWindow("Original");
	namedWindow("Processed");

	imshow("Original", image);
	imshow("Processed", Dup);


		char key = 0;
	while (key != 27)
	{
		key = waitKey(10);
	}





}