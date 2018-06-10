/*
 * image_helper.cpp
 *
 *  Created on: Apr 20, 2013
 *      Author: okan
 */

#include "image_helper.h"
#include <ros/ros.h>
#include <sensor_msgs/image_encodings.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/mat.hpp>

ImageHelper::ImageHelper() {
	isBallKnown = false;
	centerx = 0;
	centery = 0;
	//cv::namedWindow (OPENCV_WINDOW) ;
}

ImageHelper::~ImageHelper() {
	// TODO Auto-generated destructor stub
	//cv::destroyWindow (OPENCV_WINDOW) ;
}

void ImageHelper::processImage(const sensor_msgs::ImageConstPtr& imageConstPtr)
{
	if (!imageConstPtr) {
		return;
	}

	isBallKnown = false;

	cv_bridge::CvImagePtr cv_ptr;
	try
	{
		cv_ptr = cv_bridge::toCvCopy(imageConstPtr, sensor_msgs::image_encodings::BGR8);
	}
	catch (cv_bridge::Exception& e)
	{
		ROS_ERROR("cv_bridge exception: %s", e.what());
		return;
	}

	centerx = 0;
	centery = 0;
	redCount = 0;
	
    //image(i,j)[0] -> Blue, image(i,j)[1] -> Green, image(i,j)[2] -> Red
	cv::Mat_<cv::Vec3b> myImage = cv_ptr->image;
//cv::imshow(OPENCV_WINDOW,myImage);
	//cv::waitKey(3);
	//	std::cout << "row=" << cv_ptr->image.rows << " col=" << cv_ptr->image.cols  << std::endl;
	for (int i = 0; i < cv_ptr->image.rows; i++)
	{
		for (int j = 0; j < cv_ptr->image.cols; j++) {
//std::cout << "r:" <<  (double) myImage(i,j)[2] << "g:" << (double) myImage(i,j)[1] << "b:" <<(double) myImage(i,j)[0] << " " ;
			if ((double) myImage(i,j)[0] < 70 && (double) myImage(i,j)[1] < 70 && (double) myImage(i,j)[2] > 180) {
				centery += i;
				centerx += j;
				redCount++;
			}
		}
		//std::cout << std::endl;
	}

	if (redCount > 10) {
		isBallKnown = true;
		centerx = centerx / redCount;
		centery = centery / redCount;
		std::cout << "ball.x=" << centerx << " ball.y=" << centery << " redCount=" << redCount << std::endl;
	}

	//cv::imshow("Circled Image", cv_ptr->image);
	//cv::waitKey(3);
}
