#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>


using namespace cv;

class MorphoFeatures
{
private:
	int threshold1;
	// for corner
	cv::Mat cross;
	cv::Mat diamond;
	cv::Mat square;
	cv::Mat x;

	
	void applyThreshold(Mat result)
	{
		threshold(result, result, threshold1, 255, THRESH_BINARY);
	}

public:
	MorphoFeatures() : threshold1(-1), cross(5, 5, CV_8U, cv::Scalar(0)),
		diamond(5, 5, CV_8U, cv::Scalar(1)),
		square(5, 5, CV_8U, cv::Scalar(1)),
		x(5, 5, CV_8U, cv::Scalar(0)){

		// cross
		for (int i = 0; i<5; i++) {

			cross.at<uchar>(2, i) = 1;
			cross.at<uchar>(i, 2) = 1;
		}

		// diamond
		diamond.at<uchar>(0, 0) = 0;
		diamond.at<uchar>(0, 1) = 0;
		diamond.at<uchar>(1, 0) = 0;
		diamond.at<uchar>(4, 4) = 0;
		diamond.at<uchar>(3, 4) = 0;
		diamond.at<uchar>(4, 3) = 0;
		diamond.at<uchar>(4, 0) = 0;
		diamond.at<uchar>(4, 1) = 0;
		diamond.at<uchar>(3, 0) = 0;
		diamond.at<uchar>(0, 4) = 0;
		diamond.at<uchar>(0, 3) = 0;
		diamond.at<uchar>(1, 4) = 0;

		// x shaped
		for (int i = 0; i<5; i++) {

			x.at<uchar>(i, i) = 1;
			x.at<uchar>(4 - i, i) = 1;
		}
	}


	Mat getCorners(Mat image)
	{
		Mat result;
		
		dilate(image, result, cross);

		erode(result, result, diamond);

		Mat result2;

		dilate(image, result2, x);

		erode(result2, result2, square);

		absdiff(result, result, result);
		



		applyThreshold(result);

		return result;
	}

	Mat getedges(Mat image)
	{
		Mat result;
		morphologyEx(image, result, MORPH_GRADIENT, Mat());
		applyThreshold(result);

		return result;
	}
	void setThreshold(int a)
	{
		threshold1 = a;
	}


	void drawOnImage(const cv::Mat& binary,
		Mat& image) {
		Mat_<uchar>::const_iterator it =
			binary.begin<uchar>();
		cv::Mat_<uchar>::const_iterator itend = binary.end<uchar>();
	
		for (int i = 0; it != itend; ++it, ++i) {
			if (!*it)
				cv::circle(image,
				cv::Point(i%image.step, i / image.step),
				5, cv::Scalar(255, 0, 0));
		}
	}

};



int main()
{
	MorphoFeatures mor;
	mor.setThreshold(40);
	namedWindow("original");
	namedWindow("edges");
	Mat image = imread("c.jpg", 2);
	imshow("original", image);

	Mat dup = image.clone();
	Mat dup2 = image.clone();
	Mat edges;
	
	edges = mor.getedges(image);
	
	imshow("edges", edges);

	Mat corners;
	corners = mor.getCorners(dup);
	
	mor.drawOnImage(corners, dup2);
	namedWindow("Corners on Image");
	imshow("Corners on Image", dup2);

	char key = 0;
	while (key != 27)
	{
		key = waitKey(10);
	}

	return 0;
}