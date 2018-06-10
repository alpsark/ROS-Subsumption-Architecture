/*
 * general_sensor_helper.cpp
 *
 *  Created on: Apr 20, 2013
 *      Author: okan
 */

#include "general_sensor_helper.h"
#define PI 3.1415926535897932384626433f

GeneralSensorHelper::GeneralSensorHelper() {
	isObstacle = false;
	direction = 10 ; //modifieds	
	isoccupiedleft = false;
	start = false ;
}

GeneralSensorHelper::~GeneralSensorHelper() {
}

void GeneralSensorHelper::processMap(const nav_msgs::OccupancyGridConstPtr& occupancyGridConstPtr)
{
	// delegate to the related sensor helper
	mapHelper.processMap(occupancyGridConstPtr);

	
}

void GeneralSensorHelper::processImage(const sensor_msgs::ImageConstPtr& imageConstPtr)
{
	// delegate to the related sensor helper
	imageHelper.processImage(imageConstPtr);
}

void GeneralSensorHelper::processLaserScan(const sensor_msgs::LaserScanConstPtr& laserScanConstPtr)
{
	float obstacleThreshold = 0.5;
	float avgDist = 0;
	int rangeCount = 0;

	isObstacle = false;

	for(int i=laserScanConstPtr->ranges.size()/2 - 30; i<laserScanConstPtr->ranges.size()/2 + 30; i++)
	{
		// is current scan valid?
		if(laserScanConstPtr->ranges[i] < laserScanConstPtr->range_max && laserScanConstPtr->ranges[i] > laserScanConstPtr->range_min)
		{
			avgDist += laserScanConstPtr->ranges[i];
			rangeCount++;
		}
		else
		{
			//std::cout<<"0 ";
		}
	}

	avgDist = avgDist / rangeCount;

	if (avgDist < obstacleThreshold) {
		isObstacle = true;
		start = true;
		std::cout<<"there is obstacle" << std::endl;
	}

}

void GeneralSensorHelper::setRobotTransform(tf::StampedTransform& _robotTransform)
{
	robotTransform = _robotTransform;
	
	//determine direction
	double anglethreshold_1 = 0.2;    //2 degrees 
	double anglethreshold_2_3 = 0.2;    //2 degrees 
	double anglethreshold_0 = 0.35;    //2 degrees 
	double angle = tf::getYaw(robotTransform.getRotation()) ; 
		//    0  +x 0 
	  //3 +y PI/2	       1 -y -PI/2
		 //   2 -x PI
	if(angle > 0-anglethreshold_0 && angle < 0+anglethreshold_0){direction = 0;}
	else if (angle > -PI/2-anglethreshold_1 && angle < -PI/2+anglethreshold_1 ){direction = 1;}
	else if (angle > PI/2-anglethreshold_2_3 && angle < PI/2 + anglethreshold_2_3){direction = 3;}
	else if (angle < -PI+anglethreshold_2_3 || angle > PI-anglethreshold_2_3){direction = 2;}
	std::cout << "Orientation is " <<  direction << " angle is " <<  angle << std::endl;
	if(start){
		double x = robotTransform.getOrigin().x();
		double y = robotTransform.getOrigin().y();
		if(direction == 0){isoccupiedleft = mapHelper.isOccupied(x-0.5,y+1); }
		else if(direction == 3){isoccupiedleft = mapHelper.isOccupied(x-1,y-0.5); }
		else if(direction == 1){isoccupiedleft = mapHelper.isOccupied(x+1,y+0.5);}
		else if(direction == 2){isoccupiedleft = mapHelper.isOccupied(x+0.5,y-1);}
	}
	if(isoccupiedleft) {
		std::cout << "left occupied " << std::endl; 
	}
	//std::cout << "robot.rot= " << tf::getYaw(robotTransform.getRotation()) << std::endl; 
	//std::cout << "robot.x= " << robotTransform.getOrigin().x() << std::endl;
	//std::cout << "robot.y=" << robotTransform.getOrigin().y() << std::endl;
}
