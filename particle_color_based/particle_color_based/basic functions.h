
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>
#include<random>
#include<math.h>
#include<cmath>
#include<fstream>

using namespace cv;
using namespace std;

//minimum values of h and a of the car
#define MIN_h  20
#define MAX_h  40
#define MIN_a  .66
#define MAX_a  1.75


#define min(a, b) ((a < b) ? a : b)
#define max(a, b) ((a > b) ? a : b)


//for guassian noise
std::default_random_engine generator2;
std::normal_distribution<double> distribution2(0, 20);



Mat F = (Mat_<float>(6, 6) << 1, 0, 1, 0, 0, 0,
							  0, 1, 0, 1, 0, 0,
							  0, 0, 1, 0, 0, 0,
							  0, 0, 0, 1, 0, 0,
							  0, 0, 0, 0, 1, 0,
							  0, 0, 0, 0, 0, 1);
float x_n, y_n, u_n, v_n;


void motionpredict(Mat particles[],int no_of_particles,int width,int height)
{
	static int abc = 0;
	//ofstream fil_X;
	//fil_X.open("X.txt", ios::app);
	//fil_X << "\n\n\nFrame  " << ++abc << "\n\n";
	//cout << "6 ";
	for (int i = 0; i < no_of_particles; i++)
	{

		//fil_X << "Before Particle " <<i<< " " << particles[i] << "  "  << "\n";
		//cout << "7 ";
		x_n = distribution2(generator2);
		y_n = distribution2(generator2);
		u_n = distribution2(generator2);
		v_n = distribution2(generator2);
		//cout << "8 ";
		Mat Q = (Mat_<float>(6, 1) << x_n, y_n, u_n, v_n, 0, 0);
		//cout << "9 ";
		particles[i] = F*particles[i] + Q;
		//cout << "11 ";

		//checking for x and y value
		particles[i].at<float>(0, 0) = max(particles[i].at<float>(0, 0), 1);
		particles[i].at<float>(1, 0) = max(particles[i].at<float>(1, 0), 1); 
		

		particles[i].at<float>(5, 0) = max(particles[i].at<float>(5, 0), MIN_h);
		particles[i].at<float>(5, 0) = min(particles[i].at<float>(5, 0), MAX_h);


		//checking for the video to not go out of the window
		
		//first height
		if (particles[i].at<float>(1, 0) + particles[i].at<float>(5, 0) > height)
			particles[i].at<float>(5, 0) = min(height - particles[i].at<float>(5, 0), MAX_h);

		//for width
		if (particles[i].at<float>(0, 0) + particles[i].at<float>(4, 0)*particles[i].at<float>(5, 0) > width)
		{
			particles[i].at<float>(0, 0) = width -particles[i].at<float>(4, 0)*particles[i].at<float>(5, 0);
			float new_w = width - particles[i].at<float>(0, 0);
			particles[i].at<float>(4, 0) = new_w / particles[i].at<float>(5, 0);
			particles[i].at<float>(4, 0) = min(particles[i].at<float>(4, 0), MIN_a);
		}

		//fil_X << "After Particle " << i << " " << particles[i] << "  " << "\n\n";
	}


	//cout << " came from motion";

}




MatND LABhistogram(Mat image)
{
	MatND hist;

	int a_bin = 25;
	int b_bin = 25;
	
	int histSize[] = { a_bin, b_bin };

	float a_range[] = { -127, 128 };
	float b_range[] = { -127, 128 };
	
	const float* ranges[] = { a_range, b_range };


	//taking the a and b component
	int channels[] = { 1, 2 };


	calcHist(&image, 1, channels, Mat(), hist , 2, histSize, ranges, true, false);
	normalize(hist , hist , 0, 1, NORM_MINMAX, -1, Mat());

	return hist;

}


void observationmodel(Mat particles[], float weight[],Mat image, MatND target, int n,int width,int height)
{
	float r, c, r2, c2;
	static int abc = 0;
	float w, h;
	ofstream fil_X;
	float m_sum = 0;
	fil_X.open("X.txt", ios::app); cout << " i values\n";
	fil_X << "\n\n\nFrame at observation  " << ++abc << "\n\n";
	for (int i = 0; i < n; i++)
	{
		cout << i << "  ";
		r = particles[i].at<float>(0, 0);
		c = particles[i].at<float>(1, 0);
		w = particles[i].at<float>(4, 0)*particles[i].at<float>(5, 0);
		h = particles[i].at<float>(5, 0);
		cout << "a ";
		/*
		w = min(width,  w + 1);
		h = min(height, h + 1);
		*/

		if (r < 0 || c < 0)
		{
			r = max(1, r);
			c = max(1, c);
		}
		
		h = max(h, MIN_h);
		w = max(MIN_h*MIN_a, w);

		if ((c + w) > width)
			w = width - c;
		if ((r + h)>height)
			h = height - r;

		cout << " a ";
		//check
		//Rect rec(r, c, w, h);
		Rect rec(r, c, w,h);
		
		cout << " a";
		cout << r << "  " << c << "  " << w << "  " << h << "\n";
		Mat like_li = image(rec);
		cout << " a";
		MatND hist_like_li = LABhistogram(like_li);

		//bhattacharya distance
		// imshow("cropedimage", like_li);
		weight[i] = 1-compareHist(target, hist_like_li, 3);

		fil_X << "Particle "<< " " << particles[i] << "  " << weight[i] << "\n";
		//cout << weight[i] << "\n";
		//waitKey(4000);
		 //normalizing the weights
		m_sum += weight[i];


	}
	for (int i = 0; i < n; i++)
	{
		weight[i] = weight[i] / m_sum;
	}


}