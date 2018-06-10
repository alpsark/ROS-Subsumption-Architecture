/*
 * search_ball.cpp
 *
 *  Created on: Apr 28, 2018
 *      Author: alp
 */

#include "search_ball.h"
#include <math.h>
#include <tf/tf.h>
#define PI 3.1415926535897932384626433f

SearchBall::SearchBall() {
}

SearchBall::~SearchBall() {
}

void SearchBall::init()
{
	subsumption = true;
	is_turning = false;
	next_direction = generalSensorHelper-> direction ;
	left = true ;
	straight = true ;
}

void SearchBall::run()
{

	if (generalSensorHelper->imageHelper.isBallKnown) {
		subsumption = false;
	}

			//    0  +x 0 
	  //3 +y PI/2	       1 -y -PI/2
		 //   2 -x PI
	 

	if (!(generalSensorHelper-> isoccupiedleft) && left && !straight) {//left is empty

		// generate obstacle avoidance commands to get rid of the obstacle
		is_turning = true ;
		left = false ;
		straight = true  ;
		next_direction =  (generalSensorHelper-> direction +3)%4 ;
		std::cout << " TURN LEFT_1 " << next_direction <<  std::endl ;
		action.forwardCommand = 0;
		action.turnCommand = 0.4;//turn left
	}else { //go straight
		std::cout << " DUMDUZ_1 " << std::endl ;
		action.forwardCommand = 1;
		action.turnCommand = 0;//turn left

	}
	
	if(straight){		
		//go straight
		action.forwardCommand = 1;
		action.turnCommand = 0;//turn left
		std::cout << " DUMDUZ_after_turn " << std::endl ;
		if(generalSensorHelper->isoccupiedleft){
			straight = false ;
		}
	}


	if(is_turning){//first turn then go straight
		if(generalSensorHelper-> direction != next_direction){

			action.turnCommand = 0.4 ;
			action.forwardCommand = 0;
		std::cout << " TURN LEFT_2 " << std::endl ;
		}else{
			is_turning = false ;
			left = true ;
			action.forwardCommand = 1;
			action.turnCommand = 0;//stop		
		}		
	}
	
}
