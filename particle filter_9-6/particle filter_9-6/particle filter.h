#include <opencv\cv.h>
#include <opencv\highgui.h>

#include<Windows.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<stdio.h>
#include<iostream>
#include<fstream>
double uniformRandom()
{
	return ((double)(rand()) + 1.) / ((double)(RAND_MAX)+1.);
}
// return a normally distributed random number
double normalRandom()
{
	double u1 = uniformRandom();
	double u2 = uniformRandom();
	return cos(8.*atan(1.)*u2)*sqrt(-2.*log(u1));
}

/*
float mgd(float mean, float covariance)
{

	float k = 1.0 / (sqrt((2 * 22 * covariance) / 7.0);
	return k;//*exp(-1 * (()/ (2*covariance)))
}*/