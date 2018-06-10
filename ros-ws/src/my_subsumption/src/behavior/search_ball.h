/*
 * search_ball.h
 *
 *  Created on: Apr 24, 2018
 *      Author: alp
 */

#ifndef SEARCH_BALL_H_
#define SEARCH_BALL_H_

#include "../subsumption/mybehavior.h"

class SearchBall: public MyBehavior {
public:
	SearchBall();
	virtual ~SearchBall();

	void init();
	void run();

	//modified
	bool is_turning ; 
	int next_direction ;
	bool left ;
	bool straight ;

};

#endif /* SEARCH_BALL_H_ */
