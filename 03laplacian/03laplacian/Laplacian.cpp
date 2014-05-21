#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>


using namespace cv;

void laplace(Mat image)
{

	Mat result;
	result.create(image.size(), image.type());
	//result.create(image.size, image.type);

	for (int i = 1; i < image.rows - 1; i++)
	{
		const uchar* prev = image.ptr<const uchar>(i - 1);

		const uchar* present = image.ptr<const uchar>(i);

		const uchar* next = image.ptr<const uchar>(i + 1);

		uchar* output = result.ptr<uchar>(i);


		for (int j = 1; j < image.cols - 1; j++)
		{
			*output++ = saturate_cast<uchar>(5 * present[j] - present[j - 1] - present[j + 1] - prev[j] - next[j]);

		}



	}

	result.row(0).setTo(Scalar(0));
	result.row(result.rows - 1).setTo(Scalar(0));
	result.col(0).setTo(Scalar(0));
	result.col(result.cols - 1).setTo(Scalar(0));


	namedWindow("laplace_sharp");
	imshow("laplace_sharp", result);

	char key = 0;
	while (key != 27)
	{
		key = waitKey(10);
	}

	return;

}



int main()
{
	Mat image = imread("a.jpg",2);
	namedWindow("original");

	imshow("original", image);
	
	laplace(image);

	char key = 0;
	while (key != 27)
	{
		key = waitKey(10);
	}

	return 0;
}