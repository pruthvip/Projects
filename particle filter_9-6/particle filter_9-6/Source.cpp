
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include"particle filter.h"
#include<Windows.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<stdio.h>
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<math.h>
#include<random>
#include<fstream>


using namespace cv;
using namespace std;

bool flag_ = 0;
int I_rows, I_cols;


#define max 50
float dt = 1.0;
static Mat A = (Mat_<float>(4, 4) << 1.0, 0.0, dt, 0, 0, 1.0, 0.0, dt, 0.0, 0.0, 1.0, 0.0, 0, 0, 0, 1.0);
static Mat Prior = (Mat_<float>(4, 1) << 0, 0, 0, 0);
static Mat Predict = (Mat_<float>(4, 1) << 0, 0, 0, 0);
Mat Ex = (Mat_<float>(4, 4) << dt*dt / 4.0, 0, dt*dt*dt / 2.0, 0, 0, dt*dt / 4.0, 0, dt*dt*dt / 2.0, dt*dt*dt / 2.0, 0.0, dt*dt, 0, 0, dt*dt*dt / 2.0, 0, dt*dt);
float X_R = 1000;

static Mat Particle[max];
Mat Particle2[max];
float weight[max];

std::default_random_engine generator;
std::normal_distribution<double> distribution(0, 20);


void intialise_particles( int init_x,int init_y)
{
	int i;
	for (i = 0; i < max; i++)
	{
		Particle[i] = (Mat_<float>(4, 1) << init_x + distribution(generator), init_y + distribution(generator) , 0, 0);
		weight[i] = 1;
	}

}

void filter(float *a, float *b)
{
	if (flag_ == 0)
	{
		intialise_particles((int)*a, (int)*b);
		flag_ = 1;
		ofstream fil_X;
		fil_X.open("X.txt", ios::app);
		fil_X << "\n\n Particle initialisiaing";
		for (int k = 0; k < max; k++)
		{
			fil_X << Particle[k]<<"   "<<weight[k];
			fil_X << "\n";
		}

		fil_X << "\n\n Particle intilising finish";
	}
	float x_m = *a;
	float y_m = *b;
	//for the car
	Predict = A*Prior;

	//updating the particles
	float sum = 0;
	float maximum = 0;
	ofstream fil_X;
	fil_X.open("X.txt", ios::app);
	fil_X << "\n\n\n\n";
	for (int i = 0; i < max; i++)
	{

		//motion predict
		Particle[i] = A*Particle[i];
		Particle[i].at<float>(0, 0) += distribution(generator);
		Particle[i].at<float>(1, 0) += distribution(generator);
		Particle[i].at<float>(2, 0) += distribution(generator);
		Particle[i].at<float>(3, 0) += distribution(generator);

		if (Particle[i].at<float>(0, 0) < 0)
			Particle[i].at<float>(0, 0) = 0;

		if (Particle[i].at<float>(1, 0) < 0)
			Particle[i].at<float>(1, 0) = 0;
		float xW, yW;

		//observation model

		xW = exp((-1 * (x_m - Particle[i].at<float>(0, 0)) *  (x_m - Particle[i].at<float>(0, 0))) / (2.0*X_R));
		yW =  exp((-1 * (y_m - Particle[i].at<float>(1, 0)) *  (y_m - Particle[i].at<float>(1, 0)))/(2.0*X_R)  );
		weight[i] = sqrt(xW*xW + yW*yW);
		
		
		fil_X << Particle[i] << "  " <<"  " << weight[i] << "\n";
		sum += weight[i];
		if (weight[i] > maximum)
			maximum = weight[i];
	}

//	normalizing the weights;
	for (int i = 0; i < max; i++)
		weight[i] = weight[i] / sum;

	//resampling
/*
//index = int(random.random() * N)
	int index = rand() % max;
	float beta = 0.0;
		//mw = max(W)
		float mw = maximum;

	for (int i = 0; i < max; i++)
	{
		beta += rand()*2.0*mw;
		while (beta>weight[index])
		{
			beta -= weight[index];
			index = (index + 1) % max;

		}
		Particle2[i] = Particle[index];
	}
*/
	//resampling
	
	RNG rng;
	const int N=max;
	float cumSum[N];
		cumSum[0] = weight[0];
		for (int i = 1; i < N; i++)
		{
			cumSum[i] = cumSum[i - 1] + weight[i];
			cout << "  " << cumSum[i]<<"\n";
		}
		const int t = N + 1;
		float uniform[t];
		for (int i = 0; i <= N; i++)
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
			pParticles.push_back(Particle[index[i]]);
		}


	
	
	x_m = 0;
	y_m = 0;
	for (int i = 0; i < max; i++)
	{
		Particle[i] = pParticles[i];
		x_m +=  Particle[i].at<float>(0, 0);
		y_m +=  Particle[i].at<float>(1, 0);

		*a = x_m / max;;
		*b = y_m / max;;
	}




}













//our sensitivity value to be used in the absdiff() function
const static int SENSITIVITY_VALUE = 20;
//size of blur used to smooth the intensity image output from absdiff() function
const static int BLUR_SIZE = 10;
//we'll have just one object to search for
//and keep track of its position.
int theObject[2] = { 0, 0 };
//bounding rectangle of the object, we will use the center of this as its position.
Rect objectBoundingRectangle = Rect(0, 0, 0, 0);





//int to string helper function
string intToString(int number){

	//this function has a number input and string output
	std::stringstream ss;
	ss << number;
	return ss.str();
}

void searchForMovement(Mat thresholdImage, Mat &cameraFeed){




	static unsigned int time = 0;
	bool objectDetected = false;
	Mat temp;
	thresholdImage.copyTo(temp);
	//these two vectors needed for output of findContours
	vector< vector<Point> > contours;
	vector<Vec4i> hierarchy;
	//find contours of filtered image using openCV findContours function
	//findContours(temp,contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE );// retrieves all contours
	findContours(temp, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);// retrieves external contours

	//if contours vector is not empty, we have found some objects
	if (contours.size()>0)objectDetected = true;
	else objectDetected = false;

	if (objectDetected){
		//the largest contour is found at the end of the contours vector
		//we will simply assume that the biggest contour is the object we are looking for.
		vector< vector<Point> > largestContourVec;
		largestContourVec.push_back(contours.at(contours.size() - 1));
		//make a bounding rectangle around the largest contour then find its centroid
		//this will be the object's final estimated position.
		objectBoundingRectangle = boundingRect(largestContourVec.at(0));
		int xpos = objectBoundingRectangle.x + objectBoundingRectangle.width / 2;
		int ypos = objectBoundingRectangle.y + objectBoundingRectangle.height / 2;

		//update the objects positions by changing the 'theObject' array values
		theObject[0] = xpos, theObject[1] = ypos;
	}
	//make some temp x and y variables so we dont have to type out so much
	int x = theObject[0];
	int y = theObject[1];


	float ParX, ParY;
	ParX = x;
	ParY = y;
	filter(&ParX, &ParY);
	ParX = (int)ParX;
	ParY = (int)ParY;
	
	

	

	//Particle filter estimate
	circle(cameraFeed, Point(ParX, ParY), 20, Scalar(0, 0,255), 2);
	line(cameraFeed, Point(ParX, ParY), Point(ParX, ParY - 25), Scalar(0, 0,255), 2);
	line(cameraFeed, Point(ParX, ParY), Point(ParX, ParY + 25), Scalar(0, 0,255), 2);
	line(cameraFeed, Point(ParX, ParY), Point(ParX - 25, ParY), Scalar(0, 0,255), 2);
	line(cameraFeed, Point(ParX, ParY), Point(ParX + 25, ParY), Scalar(0, 0,255), 2);


	//draw some crosshairs around the object
	circle(cameraFeed, Point(x, y), 20, Scalar(0, 255, 0), 2);
	line(cameraFeed, Point(x, y), Point(x, y - 25), Scalar(0, 255, 0), 2);
	line(cameraFeed, Point(x, y), Point(x, y + 25), Scalar(0, 255, 0), 2);
	line(cameraFeed, Point(x, y), Point(x - 25, y), Scalar(0, 255, 0), 2);
	line(cameraFeed, Point(x, y), Point(x + 25, y), Scalar(0, 255, 0), 2);
	
	//write the position of the object to the screen
	putText(cameraFeed,"Tracking object at (" + intToString(x)+","+intToString(y)+")",Point(x,y),1,1,Scalar(255,0,0),2);
	 


}
int main(){


	//some boolean variables for added functionality
	bool objectDetected = false;
	//these two can be toggled by pressing 'd' or 't'
	bool debugMode = false;
	bool trackingEnabled = false;
	//pause and resume code
	bool pause = false;
	//set up the matrices that we will need
	//the two frames we will be comparing
	Mat frame1, frame2;
	//their grayscale images (needed for absdiff() function)
	Mat grayImage1, grayImage2;
	//resulting difference image
	Mat differenceImage;
	//thresholded difference image (for use in findContours() function)
	Mat thresholdImage;
	//video capture object.
	//	Mat frame1, frame2;
	string a = "f (";

	string b = ").png";
	
	unsigned int f = 1;
	frame1 = imread(a + intToString(f) + b);
	 
	intialise_particles(frame1.rows, frame1.cols);
	//for (int k = 0; k < max; k++)
	{
		//cout << Particle[k];
		//cout << "\n";
	}

	while (1){

		//we can loop the video by re-opening the capture every time the video reaches its last frame

		while (1){
			//cout << f;
			//read first frame
			//capture.read(frame1);
			string abcd = a + intToString(f) + b;
			//cout << abcd;
			//char abc = getchar();

			frame1 = imread(a + intToString(f) + b);
			//convert frame1 to gray scale for frame differencing
			cv::cvtColor(frame1, grayImage1, COLOR_BGR2GRAY);

			//grayImage1.convertTo(grayImage2, CV_32F);
			//copy second frame
			//capture.read(frame2);

			if (f == 449)
				f = 0;
			frame2 = imread(a + intToString(f + 1) + b);

			f++;
			
			//convert frame2 to gray scale for frame differencing
			cv::cvtColor(frame2, grayImage2, COLOR_BGR2GRAY);
			/*capture.set(CV_CAP_PROP_POS_FRAMES, position);
			position = position + 1;
			if (position > t)
			position = 0;*/
			//grayImage2.convertTo(grayImage2, CV_32F);
			//perform frame differencing with the sequential images. This will output an "intensity image"
			//do not confuse this with a threshold image, we will need to perform thresholding afterwards.
			cv::absdiff(grayImage1, grayImage2, differenceImage);
			//threshold intensity image at a given sensitivity value
			cv::threshold(differenceImage, thresholdImage, SENSITIVITY_VALUE, 255, THRESH_BINARY);
			if (debugMode == true){
				//show the difference image and threshold image
				cv::imshow("Difference Image", differenceImage);
				cv::imshow("Threshold Image", thresholdImage);
			}
			else{
				//if not in debug mode, destroy the windows so we don't see them anymore
				cv::destroyWindow("Difference Image");
				cv::destroyWindow("Threshold Image");
			}
			//blur the image to get rid of the noise. This will output an intensity image
			cv::blur(thresholdImage, thresholdImage, cv::Size(BLUR_SIZE, BLUR_SIZE));
			//threshold again to obtain binary image from blur output
			cv::threshold(thresholdImage, thresholdImage, SENSITIVITY_VALUE, 255, THRESH_BINARY);
			if (debugMode == true){
				//show the threshold image after it's been "blurred"

				imshow("Final Threshold Image", thresholdImage);

			}
			else {
				//if not in debug mode, destroy the windows so we don't see them anymore
				cv::destroyWindow("Final Threshold Image");
			}

			//if tracking enabled, search for contours in our thresholded image
			if (trackingEnabled){

				searchForMovement(thresholdImage, frame1);
			
				for (int k = 0; k < max; k++)
				{
					int a = (int)Particle[k].at<float>(0, 0);
					int b = (int)Particle[k].at<float>(1, 0);
					circle(frame1, Point(a, b), 1, Scalar(0, 0, 255), 2);


				}

				/*ofstream fil_X;
				fil_X.open("X.txt", ios::app);
				fil_X << "\n\n";
				for (int k = 0; k < max; k++)
				{
					fil_X << Particle[k]<<"  "<<weight[k];
					fil_X << "\n";
				}*/

			}


		
			//show our captured frame
			imshow("Frame1", frame1);
			//waitKey(10);




			//imshow("Frame1", frame2);
			//check to see if a button has been pressed.
			//this 10ms delay is necessary for proper operation of this program
			//if removed, frames will not have enough time to referesh and a blank 
			//image will appear.
			switch (waitKey(100*10 )){

			case 27: //'esc' key has been pressed, exit program.
				return 0;
			case 116: //'t' has been pressed. this will toggle tracking
				trackingEnabled = !trackingEnabled;
				if (trackingEnabled == false) cout << "Tracking disabled." << endl;
				else cout << "Tracking enabled." << endl;
				break;
			case 100: //'d' has been pressed. this will debug mode
				debugMode = !debugMode;
				if (debugMode == false) cout << "Debug mode disabled." << endl;
				else cout << "Debug mode enabled." << endl;
				break;
			case 112: //'p' has been pressed. this will pause/resume the code.
				pause = !pause;
				if (pause == true){
					cout << "Code paused, press 'p' again to resume" << endl;
					while (pause == true){
						//stay in this loop until 
						switch (waitKey()){
							//a switch statement inside a switch statement? Mind blown.
						case 112:
							//change pause back to false
							pause = false;
							cout << "Code Resumed" << endl;
							break;
						}
					}
				}



			}
		}
		//release the capture before re-opening and looping again.
		//		capture.release();
	}

	return 0;

}