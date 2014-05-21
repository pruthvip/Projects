#include <stdio.h>
#include <iostream>

#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

void readme();

/** @function main */
int main()
{/*
	if (argc != 3)
	{
		readme(); return -1;
	}
	*/
	// Load the images
	Mat image1 = imread("4.jpg");
	Mat image2 = imread("3.jpg");
	std::cout << "hjkhkhjk\n";
	//if (imag)
	Mat gray_image1;
	Mat gray_image2;
	std::cout << "hjkhkhjk\n";
	// Convert to Grayscale
	cvtColor(image1, gray_image1, CV_RGB2GRAY);
	std::cout << "hjkhkhjk\n";
	cvtColor(image2, gray_image2, CV_RGB2GRAY);
	std::cout << "hjkhkhjk\n";
	imshow("first image", image2);
	imshow("second image", image1);


	int minHessian = 400;

	SurfFeatureDetector detector(minHessian);

	std::vector< KeyPoint > keypoints_object, keypoints_scene;

	detector.detect(gray_image1, keypoints_object);
	detector.detect(gray_image2, keypoints_scene);


	SurfDescriptorExtractor extractor;

	Mat descriptors_object, descriptors_scene;

	extractor.compute(gray_image1, keypoints_object, descriptors_object);
	extractor.compute(gray_image2, keypoints_scene, descriptors_scene);


	FlannBasedMatcher matcher;
	std::vector< DMatch > matches;
	matcher.match(descriptors_object, descriptors_scene, matches);

	double max_dist = 0; double min_dist = 100;

	//-- Quick calculation of max and min distances between keypoints
	for (int i = 0; i < descriptors_object.rows; i++)
	{
		double dist = matches[i].distance;
		if (dist < min_dist) min_dist = dist;
		if (dist > max_dist) max_dist = dist;
	}

	std::vector< DMatch > good_matches;

	for (int i = 0; i < descriptors_object.rows; i++)
	{
		if (matches[i].distance < 3 * min_dist)
		{
			good_matches.push_back(matches[i]);
		}
	}
	std::vector< Point2f > obj;
	std::vector< Point2f > scene;

	for (int i = 0; i < good_matches.size(); i++)
	{
		//-- Get the keypoints from the good matches
		obj.push_back(keypoints_object[good_matches[i].queryIdx].pt);
		scene.push_back(keypoints_scene[good_matches[i].trainIdx].pt);
	}


	Mat H = findHomography(obj, scene, CV_RANSAC);



	cv::Mat result;
	warpPerspective(image1, result, H, cv::Size(image1.cols + image2.cols, image1.rows));
	cv::Mat half(result, cv::Rect(0, 0, image2.cols, image2.rows));
	image2.copyTo(half);
	imshow("Result", result);
	
	waitKey(0);
	return 0;
}

