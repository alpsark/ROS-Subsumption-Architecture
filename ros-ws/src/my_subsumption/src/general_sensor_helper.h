/*
 * general_sensor_helper.h
 *
 *  Created on: Apr 20, 2013
 *      Author: okan
 */

#ifndef GENERAL_SENSOR_HELPER_H_
#define GENERAL_SENSOR_HELPER_H_

#include "map_helper.h"
#include "image_helper.h"

#include <ros/ros.h>
#include <tf/tf.h>
#include <nav_msgs/OccupancyGrid.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>

class GeneralSensorHelper {
public:
	GeneralSensorHelper();
	virtual ~GeneralSensorHelper();

	MapHelper mapHelper;
	ImageHelper imageHelper;

	void processMap(const nav_msgs::OccupancyGridConstPtr& occupancyGridConstPtr);
	void processImage(const sensor_msgs::ImageConstPtr& imageConstPtr);

	void processLaserScan(const sensor_msgs::LaserScanConstPtr& laserScanConstPtr);

	void setRobotTransform(tf::StampedTransform& _robotTransform);

	bool isObstacle;

	tf::StampedTransform robotTransform;
	
	//modified
	int direction ;
	bool isoccupiedleft;
	bool start;

};

#endif /* GENERAL_SENSOR_HELPER_H_ */
