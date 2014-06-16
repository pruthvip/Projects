
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>
#include<random>
#include<math.h>
#include<cmath>
#include"basic functions.h"
using namespace cv;
using namespace std;


#define min(a, b) ((a < b) ? a : b)
#define max(a, b) ((a > b) ? a : b)

#define N 50

//minimum values of h and a of the car
#define MIN_h  20
#define MAX_h  40
#define MIN_a  .66
#define MAX_a  1.75

string intToString(int number){

	//this function has a number input and string output
	std::stringstream ss;
	ss << number;
	return ss.str();
}


//particles
Mat particle[N];// = (Mat_<float>(6, 1) << 0, 0, 0, 0, 0, 0);// = Mat::zeros(6, 1);
RNG rng;
//float r_num = rng.uniform(0, 1);


int main()
{

	ofstream fil_X;
	float m_sum = 0;
	fil_X.open("X.txt", ios::app);
	//for the input frame no
	string a = "f (";
	string b = ").png";
	unsigned int f = 1;
	
	//calling the 1st frame
	Mat frame1 = imread(a + intToString(f) + b);

	 //a rectangle around the car
	rectangle(frame1, Point(175, 210), Point(175+42,210+31), Scalar(0, 255, 0), 1);
	namedWindow("output");
	imshow("output", frame1);
	


	//getting the ROI
	
	Mat src = frame1;
	Rect rec(175, 210, 42, 31);

	cout << rec.x << " " << rec.y << "  " << rec.width << "  " << rec.height << "\n";
	fil_X << " car cordinates   " << rec << "\n\n";
	Mat car=src(rec);
	namedWindow("cropped");
	imshow("cropped", car);
	MatND car_hist = LABhistogram(car);
	fil_X << "Car histogram " << car_hist << "\n\n\n";
	cout << "1  ";

	f = f + 1;

	// defining the State vector for the particle
	Mat x_init = (Mat_<float>(6, 1) << rec.x, rec.y, 0, 0, (float)(rec.width) / (float)(rec.height), rec.height);
	fil_X << "Initial state vector " << x_init << "\n\n\n";

	
	//Minimum values for the car box


	cout << "2  ";

	//for a gaussian noise distribution
	std::default_random_engine generator;
	std::normal_distribution<double> distribution(0, 15);

	char h = getchar();
	float weight[N];

	cout << "3  ";


	fil_X << "Particle intitalisation   \n\n";
	//initalising the particles
	for (int i = 0; i < N; i++)
	{


		particle[i] = (Mat_<float>(6, 1) << 0, 0, 0, 0, 0, 0);
		particle[i].at<float>(0, 0) = rec.x + distribution(generator);//x
		particle[i].at<float>(1, 0) = rec.y + distribution(generator);//y
		particle[i].at<float>(2, 0) = 0;//vel(x)
		particle[i].at<float>(3, 0) = 0;//vel(y)
		particle[i].at<float>(4, 0) =  min(0.66 + abs(rng.uniform(0.f, 1.f)), MAX_a);//a
		particle[i].at<float>(5, 0) = rec.height;// +10 + rng.uniform(0, 1);//vel(h)
		weight[i] = 1.0 / N;
		fil_X << "Particle " <<i<<"   "<< particle[i]<<"  "<<weight[i] << "\n";
	}


	cout << "4  ";
	waitKey(4000);
	//here the video starts
	while (1)
	{
		fil_X << "Frame  " <<f << "\n\n";
		//cout << "5 ";
		frame1 = imread(a + intToString(f) + b);
		f = f + 1;
		//motion predict
		fil_X << "going to  motion predict \n\n\n ";
		motionpredict(particle,N,frame1.cols-1,frame1.rows-1);
		cout << "came from motion  \n";
		 
		 
		//observation model and weigh assignment
		cout << "go to observation\n";
		observationmodel(particle,weight,frame1,car_hist,N,frame1.cols-1,frame1.rows-1);
		cout << " from observation\n";
		//resampling coded here only
		float cumSum[N];
		cumSum[0] = weight[0];
		for (int i = 1; i < N; i++)
		{
			cumSum[i] = cumSum[i - 1] + weight[i];
			cout << "  " << cumSum[i]<<"\n";
		}
		float uniform[N+1];
		for (int i = 1; i <= N; i++)
		{
			uniform[i] = rng.uniform(0.f, 1.f);
			cout << uniform[i] << "   ";
		}
		sort(uniform, uniform+N+1);
		uniform[N + 1] = 1.0;
		
		int i, j;
		i = j = 0;
		int index[N];
		while (i < N)
		{
			if (uniform[i] < cumSum[j])
			{
				index[i] = j;
				i = i + 1;
			}
			else
			{
				j = j + 1;
			}

		}
		std::vector<Mat> pParticles;
		for (int i = 0; i < N; i++)
		{
			pParticles.push_back(particle[index[i]]);
		}





		/*int qstart = 0;
		
		std::vector<Mat> pParticles;
		for (int p = 0; p < N; p++)
		{
			for (int q = qstart; q < N; q++)
			{
				if (uniform[p] <= cumSum[q])
				{
					pParticles.push_back(particle[q]);
					qstart = q;
					break;
				}

			}
		}
		*/
		//putting back again
		float x_mean = 0;
		float y_mean = 0;
		float w_mean = 0;
		float h_mean = 0;
		static int abc = 0;
		ofstream fil_X;
		fil_X.open("X.txt", ios::app);
		fil_X << "\n\n\nFrame after resampling " << ++abc << "\n\n";

		for (int i = 0; i < N; i++)
		{
			particle[i] = pParticles[i];
			fil_X << "Particle " << " " << particle[i] << "  " << weight[i] << "\n";
			x_mean += particle[i].at<float>(0, 0);
			y_mean += particle[i].at<float>(1, 0);
			w_mean += particle[i].at<float>(4, 0)*particle[i].at<float>(5,0);
			h_mean += particle[i].at<float>(5, 0);
		}

		pParticles.clear();
		int xx = (int)(x_mean / N);
		int yy = (int)(y_mean / N);
		int ww = (int)(w_mean / N);
		int hh = (int)(h_mean / N);
		int xx2 = xx + hh;
		int yy2 = yy + ww;
		xx2 = min(frame1.cols-1, xx2);
		yy2 = min(frame1.rows - 1, yy2);
		rectangle(frame1, Point(xx, yy), Point(xx2, yy2), Scalar(0, 255, 0), 1);
		imshow("output", frame1);
		cout << "printed the frame";
		//waitKey();
		//switch key for controlling the output
		switch (waitKey(5000)){

		case 27: //'esc' key has been pressed, exit program.
			return 0;
		}
	
	}
	waitKey();

	return 0;
}