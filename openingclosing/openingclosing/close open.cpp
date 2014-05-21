#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>


using namespace cv;



void open(Mat image)
{
	erode(image, image, Mat());
	dilate(image, image, Mat());
	return;

}

void close(Mat image)
{
	dilate(image, image, Mat());
	erode(image, image, Mat());
	return;
}



int main()
{

	Mat image = imread("b.jpg", 2);

	Mat image2 = image.clone();

	close(image);
	open(image2);
	
	namedWindow("open");
	namedWindow("close");
	
	imshow("open", image);
	imshow("close", image2);



	char key = 0;
	while (key != 27)
	{
		key = waitKey(10);
	}


}