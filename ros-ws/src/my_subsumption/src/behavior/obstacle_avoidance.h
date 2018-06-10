/*
 * obstacle_avoidance.h
 *
 *  Created on: Apr 20, 2013
 *      Author: okan
 */

#ifndef OBSTACLE_AVOIDANCE_H_
#define OBSTACLE_AVOIDANCE_H_

#include "../subsumption/mybehavior.h"

class ObstacleAvoidance: public MyBehavior {
public:
	ObstacleAvoidance();
	virtual ~ObstacleAvoidance(); 

	void init();
	void run();
	//modified
	bool is_turning ; 
	int next_direction ;
};

#endif /* OBSTACLE_AVOIDANCE_H_ */
