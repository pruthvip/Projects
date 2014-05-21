#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
using namespace cv;

class ColorDetector
{
private:
	int minDist;
	Vec3b target;
	Mat result;

	int GetDistance(Vec3b& color)
	{
		return abs(color[0] - target[0]) + abs(color[1] - target[1]) + abs(color[2] - target[2]);

	}

public:
	//consturctor

	ColorDetector() :minDist(100){
		target[0] = target[1] = target[2] = 0;

	}


	void setmindistance(int a)
	{
		minDist = a;


	}
	void SetTargetColor(int red, int green, int blue)
	{
		target[0] = blue;
		target[1] = green;
		target[2] = red;


	}

	void process(Mat &image)
	{
		Mat image2 = image.clone();
		Mat_<Vec3b>::iterator it = image.begin<Vec3b>();
		Mat_<Vec3b>::iterator itend = image.end<Vec3b>();
		Mat_<Vec3b>::iterator result = image2.begin<Vec3b>();

		for (; it != itend; it++,result++)
		{
			if (GetDistance(*it) < minDist)
			{
				result[0] = 0;
				result[1] = 0;
				result[2] = 0;
			}

		}

		namedWindow("modified");
		imshow("modified", image2);
		waitKey(10000);

	}

};