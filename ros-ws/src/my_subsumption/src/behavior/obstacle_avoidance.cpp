/*
 * obstacle_avoidance.cpp
 *
 *  Created on: Apr 20, 2013
 *      Author: okan
 */

#include "obstacle_avoidance.h"
#define PI 3.1415926535897932384626433f
ObstacleAvoidance::ObstacleAvoidance() {
}

ObstacleAvoidance::~ObstacleAvoidance() {
}

void ObstacleAvoidance::init() {
	is_turning = false;
	next_direction = generalSensorHelper-> direction ;

}

void ObstacleAvoidance::run() {
		//    0  +x 0 
	  //3 +y PI/2	       1 -y -PI/2
		 //   2 -x PI
	 
	if(is_turning){
		if(generalSensorHelper-> direction != next_direction){

			subsumption = true;
			action.turnCommand = -0.4 ;
		}else{
			subsumption = false;
			is_turning = false ;
			action.turnCommand = 0;//stop		
		}		
	}else{
		subsumption = false;
	}

	if (generalSensorHelper->isObstacle) {//robot sees an obstacle
		// generate obstacle avoidance commands to get rid of the obstacle
		subsumption = true;
		is_turning = true ;
		next_direction =  (generalSensorHelper-> direction +1)%4 ;
		action.forwardCommand = 0;
		action.turnCommand = -0.4;//turn right
	}
}
