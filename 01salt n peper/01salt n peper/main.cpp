#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>


using namespace cv;


void salt(Mat Image, int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		int p = rand()%Image.rows;
		int q = rand()%Image.cols;

		Image.at<Vec3b>(p, q)[0] = 255;
		Image.at<Vec3b>(p, q)[1] = 255;
		Image.at<Vec3b>(p, q)[2] = 255;
	}

	return;
}

int main()
{
	Mat image = imread("a.jpg");
	Mat result;
	namedWindow("Picture");
	namedWindow("Salt");
	char key = 0;
	imshow("Picture", image);

	salt(image, 3000);

	imshow("Salt", image);
	while (key != 27)
	{
		key = waitKey(10);
	}

	return 0;
}