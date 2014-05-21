#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>

using namespace cv;

int main()
{
	Mat Image = imread("download.jpg");

	namedWindow("hello");
	imshow("hello", Image);

	waitKey(5000);
	return 1;


}