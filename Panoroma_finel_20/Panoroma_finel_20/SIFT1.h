
#include<iostream>

#include <stdio.h>

#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\features2d\features2d.hpp>
#include<opencv2\nonfree\nonfree.hpp>
#include<opencv2\calib3d\calib3d.hpp>



using namespace cv;
using namespace std;

class SIFT1{

private:
	Mat image_orig;
	Mat Scale_spaces[4][6];
	Mat LOG_img[4][4];
	Mat Extrema[4][2];
	Mat image_temp;
	Mat middle, up, down;
	Mat image1,image2;



	void BuildScaleSpace()
	{

		cout << "in build space" <<endl;
		int i, j; 
			//image should be in grey scale
		cout << endl<<image_temp.rows << image_temp.cols << endl;
			GaussianBlur(image_temp, image_temp,  Size(5, 5), 0.5);
			//resize(image_temp, image_temp, Size(image_temp.cols * 2, image_temp.rows * 2), 0, 0, 1);
			cout << image_temp.rows << image_temp.cols << endl;
			Scale_spaces[0][0] =image_temp;
			cout << endl << image_temp.rows << image_temp.cols << endl;
			GaussianBlur(Scale_spaces[0][0], Scale_spaces[0][0],  Size(5, 5), 1);
			double int_sigma = sqrt(2) / 2;
			double sigma = int_sigma;;
			double mid;
			double power = 1.0;
			cout << "\n before for loop";
			for (i = 0; i < 4; i++)
			{

				if (i>0)
				{
					sigma = mid;
					Scale_spaces[i][0] = image_temp;
					resize(image_temp, Scale_spaces[i][0], Size(image_temp.cols / power, image_temp.rows / power), 0, 0, 1);
					cout << endl << "after resizing" << Scale_spaces[i][0].rows << Scale_spaces[i][0].cols << endl;
				}
				
				for (j = 1; j <= 5; j++)
				{
					if (j == 2)
						mid = sigma;
			//		printf(" %f  ", sigma);
							GaussianBlur(Scale_spaces[i][j-1], Scale_spaces[i][j],  Size(5, 5), sigma);
					sigma = sigma*sqrt(2);

				}
		//		printf("\n");
				power = power * 2;
			}




	}

	void ShowScaleSpace()
	{
		cout << "\n show scale\n\n";
		namedWindow("image", CV_WINDOW_AUTOSIZE);
		int i, j;
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j <= 5; j++)
			{
				cout << i<<"   "<<j<<endl;
				cout << Scale_spaces[i][j].rows<<"  " << Scale_spaces[i][j].cols << endl;
				imshow("image", Scale_spaces[i][j]);
				cvWaitKey(700);
			}
		}

	}

	void FindLOG()
	{
		cout << endl << "IN LOG  " << endl;
		int i;
		int j;
		for (i = 0; i < 4; i++)
		{
			for (j = 1; j < 5; j++)
			{
				addWeighted(Scale_spaces[i][j], 1, Scale_spaces[i][j + 1], -1,0, LOG_img[i][j - 1]);
			}
		}

	}

	void FindMaxMin()
	{

		cout << endl << "IN findmaxmin  " << endl; return;
		int i;
		int j;
		int xiter, yiter;
		for (i = 0; i < 4; i++)
		{
			for (j = 1; j < 3; j++)
			{

				 cout << LOG_img[i][j].channels();
				middle = LOG_img[i][j].clone();
				up = LOG_img[i][j - 1].clone();
				down = LOG_img[i][j + 1].clone();

				for (yiter = 1; yiter < middle.rows-1; yiter++)
				{
					for (xiter = 1; xiter < middle.cols-1; xiter++)
					{
						cout << i << "  " << j << "  " << yiter << "  " << xiter<< "  "<<endl;
						double currentPixel = middle.at<uchar>(yiter, xiter);
						cout << "1 ";
						cout << endl<<yiter << "  " << xiter << "  " << endl;
						// Check for a maximum
						if (currentPixel> middle.at<uchar>(yiter, xiter + 1) &&
							currentPixel> middle.at<uchar>(yiter, xiter - 1) &&
							currentPixel > middle.at<uchar>(yiter + 1, xiter) &&
							currentPixel > middle.at<uchar>(yiter + 1, xiter - 1) &&
							currentPixel > middle.at<uchar>(yiter, xiter + 1) &&
							currentPixel > middle.at<uchar>(yiter - 1, xiter) &&
							currentPixel > middle.at<uchar>(yiter - 1, xiter + 1) &&
							currentPixel > middle.at<uchar>(yiter - 1, xiter - 1) &&

							currentPixel > up.at<uchar>(yiter, xiter) &&
							currentPixel > up.at<uchar>(yiter, xiter + 1) &&
							currentPixel > up.at<uchar>(yiter, xiter - 1) &&
							currentPixel > up.at<uchar>(yiter + 1, xiter) &&
							currentPixel > up.at<uchar>(yiter + 1, xiter - 1) &&
							currentPixel > up.at<uchar>(yiter, xiter + 1) &&
							currentPixel > up.at<uchar>(yiter - 1, xiter) &&
							currentPixel > up.at<uchar>(yiter - 1, xiter + 1) &&
							currentPixel > up.at<uchar>(yiter - 1, xiter - 1) &&

							currentPixel > down.at<uchar>(yiter, xiter) &&
							currentPixel > down.at<uchar>(yiter, xiter + 1) &&
							currentPixel > down.at<uchar>(yiter, xiter - 1) &&
							currentPixel > down.at<uchar>(yiter + 1, xiter) &&
							currentPixel > down.at<uchar>(yiter + 1, xiter - 1) &&
							currentPixel > down.at<uchar>(yiter, xiter + 1) &&
							currentPixel > down.at<uchar>(yiter - 1, xiter) &&
							currentPixel > down.at<uchar>(yiter - 1, xiter + 1) &&
							currentPixel > down.at<uchar>(yiter - 1, xiter - 1)
							)
						{
							cout << "inside, updating extrema  ";
							if (Extrema[i][j - 1].empty() == true)
								cerr << "Fatal error" << endl;
							Extrema[i][j - 1].at<uchar>(xiter, yiter) = 255;
						}

						else if (currentPixel< middle.at<uchar>(yiter, xiter + 1) &&
							currentPixel< middle.at<uchar>(yiter, xiter - 1) &&
							currentPixel < middle.at<uchar>(yiter + 1, xiter) &&
							currentPixel < middle.at<uchar>(yiter + 1, xiter - 1) &&
							currentPixel < middle.at<uchar>(yiter, xiter + 1) &&
							currentPixel < middle.at<uchar>(yiter - 1, xiter) &&
							currentPixel < middle.at<uchar>(yiter - 1, xiter + 1) &&
							currentPixel < middle.at<uchar>(yiter - 1, xiter - 1) &&

							currentPixel < up.at<uchar>(yiter, xiter) &&
							currentPixel < up.at<uchar>(yiter, xiter + 1) &&
							currentPixel < up.at<uchar>(yiter, xiter - 1) &&
							currentPixel < up.at<uchar>(yiter + 1, xiter) &&
							currentPixel < up.at<uchar>(yiter + 1, xiter - 1) &&
							currentPixel < up.at<uchar>(yiter, xiter + 1) &&
							currentPixel < up.at<uchar>(yiter - 1, xiter) &&
							currentPixel < up.at<uchar>(yiter - 1, xiter + 1) &&
							currentPixel < up.at<uchar>(yiter - 1, xiter - 1) &&

							currentPixel < down.at<uchar>(yiter, xiter) &&
							currentPixel < down.at<uchar>(yiter, xiter + 1) &&
							currentPixel < down.at<uchar>(yiter, xiter - 1) &&
							currentPixel < down.at<uchar>(yiter + 1, xiter) &&
							currentPixel < down.at<uchar>(yiter + 1, xiter - 1) &&
							currentPixel < down.at<uchar>(yiter, xiter + 1) &&
							currentPixel < down.at<uchar>(yiter - 1, xiter) &&
							currentPixel < down.at<uchar>(yiter - 1, xiter + 1) &&
							currentPixel < down.at<uchar>(yiter - 1, xiter - 1)
							)
						{
							Extrema[i][j - 1].at<uchar>(xiter, yiter) = 255;
						}

						else
							Extrema[i][j - 1].at<uchar>(xiter, yiter) = 0;
					}




				}
			}
		}
	}
	




	
public: 
	SIFT1(Mat Image1)
	{	image_orig = Image1;
	image_temp = Image1;
	cout << "in constructor\n";
	}
	
	void DoSIFT()
	{
		cout << "in do sift\n";
		BuildScaleSpace();
		 ShowScaleSpace();
		FindLOG();
		FindMaxMin();
		

	}
};