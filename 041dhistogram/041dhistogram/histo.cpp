#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>

using namespace cv;


class Histogram1D
{

private:
	int histSize[1];  
	float hranges[2]; 
	const float* ranges[1];
	int channels[1]; // 
public:
	Histogram1D() {
		histSize[0] = 256;
		hranges[0] = 0.0;
		hranges[1] = 255.0;
		ranges[0] = hranges;
		channels[0] = 0;  
	}

	MatND getHistogram(const cv::Mat &image) {
		cv::MatND hist;
		// Compute histogram
		cv::calcHist(&image,
			1,
			channels,
			cv::Mat(),
			hist, 
			1, 
			histSize,
			ranges 
			);
		return hist;
	}

};



int main()
{
	Mat image = imread("a.jpg",2);
	namedWindow("Picture");

	imshow("Picture", image);
	Histogram1D h;

	MatND histo = h.getHistogram(image);

	for (int i = 0; i < 256; i++)
		std::cout << "value at  i " <<i<<" is   " << histo.at<float>(i) << "\n";
	char key = 0;

	Mat threshl;

	threshold(image, threshl, 170, 255, THRESH_BINARY);

	namedWindow("thresholded");
	imshow("thresholded", threshl);

	while (key != 27)
	{
		key = waitKey(10);
	}

	return 0;

}