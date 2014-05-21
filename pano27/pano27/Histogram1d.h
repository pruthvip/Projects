/*#include<opencv2\highgui\highgui.hpp>
#include<opencv2\core\core.hpp>
#include<opencv2\imgproc\imgproc.hpp>

using namespace std;
using namespace cv;

class Histogram1d{
private:
	int histSize[1];// no of bins, i.e 256, grey scale image
	float hranges[2];//min,max value
	int channels[1];//no of channels
	const float* ranges[1];
public:
	//constructor

	Histogram1d()
	{
		histSize[0] = 256;
		hranges[0] = 0.0;
		hranges[1] = 255.0;
		ranges[0] = hranges;
		channels[0] = 0;//one channel

	}


	// returning histogram values

	MatND getHistogram(Mat &image)
	{
		MatND hist;

		calcHist(&image, 1, channels, Mat(), hist,1, histSize, ranges);
		return hist;

	}


};*/