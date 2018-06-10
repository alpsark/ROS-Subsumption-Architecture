/*
 * my_subsumption.cpp
 *
 *  Created on: Apr 19, 2013
 *      Author: okan
 */

#include <ros/ros.h>
#include <std_msgs/Float64.h>

#include <tf/transform_listener.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/LaserScan.h>
#include <nav_msgs/OccupancyGrid.h>
#include <geometry_msgs/Twist.h>

#include "general_sensor_helper.h"

#include "subsumption/myarbitrator.h"
#include "subsumption/mybehavior.h"

#include "behavior/obstacle_avoidance.h"
#include "behavior/goto_ball.h"
#include "behavior/search_ball.h"
/**
 * The node which runs simple subsumption architecture
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char** argv)
{

	ros::init(argc,argv,"my_subsumption");
	ros::NodeHandle nh;
	ros::Rate rate(30);

	// construct general sensor helper
	GeneralSensorHelper sensorHelper;

	// construct publishers and subscribers
	ros::Publisher twistCommandPublisher = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1);

	ros::Subscriber imageSubs = nh.subscribe("/vrep/kinectRGBImage", 10, &GeneralSensorHelper::processImage, &sensorHelper);
	ros::Subscriber laserSubs = nh.subscribe("/scan", 10,  &GeneralSensorHelper::processLaserScan, &sensorHelper);
	ros::Subscriber mapSubs = nh.subscribe("/map", 10, &GeneralSensorHelper::processMap, &sensorHelper);

	// construct transform listener
	tf::TransformListener transformListener;
	tf::StampedTransform robotTransform;

	// create arbitrator and general sensor helper
	MyArbitrator arbitrator(&sensorHelper);

	// create behaviors
	ObstacleAvoidance* obstacleAvoidance = new ObstacleAvoidance();
	GotoBall* gotoBall = new GotoBall();
	//TODO: create your behaviour here (search ball behaviour)
	SearchBall* searchBall = new SearchBall();
	// add behaviors to the arbitrator in the order of priority.
	// level 0 is the first and level 1 is the second and goes on
	arbitrator.addBehavior(obstacleAvoidance);
	arbitrator.addBehavior(gotoBall);
	//TODO: add your behavior as the last level
	arbitrator.addBehavior(searchBall);
	// ros loop
	while(ros::ok())
	{

		// if map transform is active get pose of the robot according to map
		if (transformListener.canTransform("map","base_link",ros::Time(0))) {
			transformListener.lookupTransform("map","base_link", ros::Time(0), robotTransform);
			sensorHelper.setRobotTransform(robotTransform);
		}

		
		// run the arbitrator
		arbitrator.run();

		// get action from the arbitrator
		MyAction action = arbitrator.getAction();

		// set the twist command to drive the robot
		geometry_msgs::Twist cmd;
		cmd.linear.x = action.forwardCommand;
		//left postive right negative
		cmd.angular.z = action.turnCommand;
		//std::cout << "forw " << action.forwardCommand << std::endl;
		twistCommandPublisher.publish(cmd);

		ros::spinOnce();
		rate.sleep();
	}

	return 0;
}
