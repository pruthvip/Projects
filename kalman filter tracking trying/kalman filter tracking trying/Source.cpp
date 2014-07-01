//motionTracking.cpp

#include <opencv\cv.h>
#include <opencv\highgui.h>

#include<Windows.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<stdio.h>
#include<iostream>
#include<fstream>



using namespace cv;

using namespace std;




//our sensitivity value to be used in the absdiff() function
const static int SENSITIVITY_VALUE = 20;
//size of blur used to smooth the intensity image output from absdiff() function
const static int BLUR_SIZE = 10;
//we'll have just one object to search for
//and keep track of its position.
int theObject[2] = {0,0};
//bounding rectangle of the object, we will use the center of this as its position.
Rect objectBoundingRectangle = Rect(0,0,0,0);



ofstream fil_X, fil_Xk, fil_Y, fil_Yk;
//kalman properties
float dt = 1;//in sec
float M_N_z_x = 1;
float M_N_z_y = 1;

float GN_x = 0.1;
float GN_y = 0.1;
float a = 0.001;
Mat A = (Mat_<float>(4, 4) << 1.0, 0.0, dt, 0,     0, 1.0, 0.0, dt,    0.0,0.0,1.0,0.0,  0,0,0,1.0);
Mat B = (Mat_<float>(4, 1) << dt*dt / 2.0, dt*dt / 2.0, dt, dt);
Mat H = (Mat_<float>(2, 4) << 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0);
Mat Ez = (Mat_<float>(2, 2) <<GN_x*GN_x,0,GN_y*GN_y,0 );
Mat Ex = (Mat_<float>(4, 4) << dt*dt / 4.0, 0, dt*dt*dt / 2.0, 0, 0, dt*dt / 4.0, 0, dt*dt*dt / 2.0, dt*dt*dt / 2.0, 0.0, dt*dt, 0, 0, dt*dt*dt / 2.0, 0, dt*dt);

Mat P = Ex;

Mat Prior = (Mat_<float>(4, 1) << 0, 0, 0, 0);
Mat Predict = (Mat_<float>(4, 1) << 0, 0, 0, 0);

Mat I = Mat::eye(4, 4, CV_32F);



void Kalman_Filter(float *Zx, float *Zy)
{
	//cout << "1";
	Mat Zt = (Mat_<float>(2, 1) << *Zx, *Zy);
	//prediction
	//cout << "2";
	Predict = A*Prior;// +B*a;
	//cout << "3";
	P = P*P*A.t() + Ex;
	//cout << "4";
	//measurement uopdate
	Mat Kt = P*H.t()*(H*P*H.t() + Ez);
	//cout << "5";
	Prior = Predict + Kt*(Zt - H*Predict);
	//cout << "6";
	P = (I - Kt*H)*P;
	//cout << "7";
	*Zx = Prior.at<float>(0, 0);
	*Zy = Prior.at<float>(1, 0);
	//cout << "8";
	return;

}

//int to string helper function
string intToString(int number){

	//this function has a number input and string output
	std::stringstream ss;
	ss << number;
	return ss.str();
}

void searchForMovement(Mat thresholdImage, Mat &cameraFeed){
 

	 ofstream fil_X,fil_Xk,fil_Y,fil_Yk;
	fil_X.open("X.txt", ios::app);
	fil_Xk.open("Xk.txt", ios::app);
	fil_Y.open("Y.txt", ios::app);
	fil_Yk.open("Yk.txt", ios::app);
	 

	static unsigned int time = 0;
	bool objectDetected = false;
	Mat temp;
	thresholdImage.copyTo(temp);
	//these two vectors needed for output of findContours
	vector< vector<Point> > contours;
	vector<Vec4i> hierarchy;
	//find contours of filtered image using openCV findContours function
	//findContours(temp,contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE );// retrieves all contours
	findContours(temp,contours,hierarchy,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE );// retrieves external contours

	//if contours vector is not empty, we have found some objects
	if(contours.size()>0)objectDetected=true;
	else objectDetected = false;

	if(objectDetected){
		//the largest contour is found at the end of the contours vector
		//we will simply assume that the biggest contour is the object we are looking for.
		vector< vector<Point> > largestContourVec;
		largestContourVec.push_back(contours.at(contours.size()-1));
		//make a bounding rectangle around the largest contour then find its centroid
		//this will be the object's final estimated position.
		objectBoundingRectangle = boundingRect(largestContourVec.at(0));
		int xpos = objectBoundingRectangle.x+objectBoundingRectangle.width/2;
		int ypos = objectBoundingRectangle.y+objectBoundingRectangle.height/2;

		//update the objects positions by changing the 'theObject' array values
		theObject[0] = xpos , theObject[1] = ypos;
	}
	//make some temp x and y variables so we dont have to type out so much
	int x = theObject[0];
	int y = theObject[1];
	
	static int flagg = 0;
	if(flagg<5)
		flagg=flagg+1;
	if (flagg == 3)
	{
		Prior = (Mat_<float>(4, 1) << x, y, 0, 0);
		 
	}
	float KalX; float KalY;
	KalX = x;
	KalY = y;

	Kalman_Filter(&KalX, &KalY);

	KalX = (int)KalX;
	KalY = (int)KalY;
	/*
	fil_X <<","<< x << ", " << time;// .open("X.txt");
	fil_Xk <<","<< KalX <<", "<<time;// .open("Xk.txt");
	fil_Y << "," << y << ", " << time;
	fil_Yk << "," << KalY << ", " << time;
	time++;*/

	//draw some crosshairs around the object for kalman filter
	circle(cameraFeed, Point(KalX, KalY), 25, Scalar(0, 0,255), 2);
	line(cameraFeed, Point(KalX, KalY), Point(KalX, KalY - 25), Scalar(0, 0, 255), 2);
	line(cameraFeed, Point(KalX, KalY), Point(KalX, KalY + 25), Scalar(0, 0,255), 2);
	line(cameraFeed, Point(KalX, KalY), Point(KalX - 25, KalY), Scalar(0, 0,255), 2);
	line(cameraFeed, Point(KalX, KalY), Point(KalX + 25, KalY), Scalar(0, 0,255), 2);




	

	//draw some crosshairs around the object
	circle(cameraFeed,Point(x,y),20,Scalar(0,255,0),2);
	line(cameraFeed,Point(x,y),Point(x,y-25),Scalar(0,255,0),2);
	line(cameraFeed,Point(x,y),Point(x,y+25),Scalar(0,255,0),2);
	line(cameraFeed,Point(x,y),Point(x-25,y),Scalar(0,255,0),2);
	line(cameraFeed,Point(x,y),Point(x+25,y),Scalar(0,255,0),2);

	//write the position of the object to the screen
	//putText(cameraFeed,"Tracking object at (" + intToString(x)+","+intToString(y)+")",Point(x,y),1,1,Scalar(255,0,0),2);
	//putText(cameraFeed, "Tracking object at (" + intToString(KalX) + "," + intToString(KalY) + ")", Point(KalX, KalY), 1, 1, Scalar(255, 0, 0), 2);

	

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
	Mat frame1,frame2;
	//their grayscale images (needed for absdiff() function)
	Mat grayImage1,grayImage2;
	//resulting difference image
	Mat differenceImage;
	//thresholded difference image (for use in findContours() function)
	Mat thresholdImage;
	//video capture object.
	VideoCapture capture(0);



	while(1){

		//we can loop the video by re-opening the capture every time the video reaches its last frame

		 capture.open("bouncingBall.avi");
		/*if (capture.isOpened() == false)
		{
			std::cout << "error";
			return 0;
		}*/
		if(!capture.isOpened()){
			cout<<"ERROR ACQUIRING VIDEO FEED\n";
			getchar();
			return -1;
		}
		long t = static_cast<long>(
			capture.get(CV_CAP_PROP_FRAME_COUNT));
		double rate = capture.get(CV_CAP_PROP_FPS);
		int delay = 1000 / rate;

		// goto frame 100
		double position = 2;
		
		//check if the video has reach its last frame.
		//we add '-1' because we are reading two frames from the video at a time.
		//if this is not included, we get a memory error!
		 while(capture.get(CV_CAP_PROP_POS_FRAMES)<capture.get(CV_CAP_PROP_FRAME_COUNT)-1){
		//while (1){

			//read first frame
			capture.read(frame1);
			//convert frame1 to gray scale for frame differencing
			cv::cvtColor(frame1,grayImage1,COLOR_BGR2GRAY);

			//grayImage1.convertTo(grayImage2, CV_32F);
			//copy second frame
			capture.read(frame2);
			//convert frame2 to gray scale for frame differencing
			cv::cvtColor(frame2,grayImage2,COLOR_BGR2GRAY);
			/*capture.set(CV_CAP_PROP_POS_FRAMES, position);
			position = position + 1;
			if (position > t)
				position = 0;*/
			//grayImage2.convertTo(grayImage2, CV_32F);
			//perform frame differencing with the sequential images. This will output an "intensity image"
			//do not confuse this with a threshold image, we will need to perform thresholding afterwards.
			cv::absdiff(grayImage1,grayImage2,differenceImage);
			//threshold intensity image at a given sensitivity value
			cv::threshold(differenceImage,thresholdImage,SENSITIVITY_VALUE,255,THRESH_BINARY);
			if(debugMode==true){
				//show the difference image and threshold image
				cv::imshow("Difference Image",differenceImage);
				cv::imshow("Threshold Image", thresholdImage);
			}else{
				//if not in debug mode, destroy the windows so we don't see them anymore
				cv::destroyWindow("Difference Image");
				cv::destroyWindow("Threshold Image");
			}
			//blur the image to get rid of the noise. This will output an intensity image
			cv::blur(thresholdImage,thresholdImage,cv::Size(BLUR_SIZE,BLUR_SIZE));
			//threshold again to obtain binary image from blur output
			cv::threshold(thresholdImage,thresholdImage,SENSITIVITY_VALUE,255,THRESH_BINARY);
			if(debugMode==true){
				//show the threshold image after it's been "blurred"

				imshow("Final Threshold Image",thresholdImage);

			}
			else {
				//if not in debug mode, destroy the windows so we don't see them anymore
				cv::destroyWindow("Final Threshold Image");
			}

			//if tracking enabled, search for contours in our thresholded image
			if(trackingEnabled){

				searchForMovement(thresholdImage,frame1);
			}

			//show our captured frame
			imshow("Frame1",frame1);
			//waitKey(10);




				//imshow("Frame1", frame2);
			//check to see if a button has been pressed.
			//this 10ms delay is necessary for proper operation of this program
			//if removed, frames will not have enough time to referesh and a blank 
			//image will appear.
			switch (waitKey( delay*2  )){
				 
			case 27: //'esc' key has been pressed, exit program.
				return 0;
			case 116: //'t' has been pressed. this will toggle tracking
				trackingEnabled = !trackingEnabled;
				if(trackingEnabled == false) cout<<"Tracking disabled."<<endl;
				else cout<<"Tracking enabled."<<endl;
				break;
			case 100: //'d' has been pressed. this will debug mode
				debugMode = !debugMode;
				if(debugMode == false) cout<<"Debug mode disabled."<<endl;
				else cout<<"Debug mode enabled."<<endl;
				break;
			case 112: //'p' has been pressed. this will pause/resume the code.
				pause = !pause;
				if(pause == true){ cout<<"Code paused, press 'p' again to resume"<<endl;
				while (pause == true){
					//stay in this loop until 
					switch (waitKey()){
						//a switch statement inside a switch statement? Mind blown.
					case 112: 
						//change pause back to false
						pause = false;
						cout<<"Code Resumed"<<endl;
						break;
					}
				}
				}



			}
		}
		//release the capture before re-opening and looping again.
		capture.release();
	}

	return 0;

}