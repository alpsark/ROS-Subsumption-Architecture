/*
 * goto_ball.h
 *
 *  Created on: Apr 20, 2013
 *      Author: okan
 */

#ifndef GOTO_BALL_H_
#define GOTO_BALL_H_

#include "../subsumption/mybehavior.h"

class GotoBall: public MyBehavior {
public:
	GotoBall();
	virtual ~GotoBall();

	void init();
	void run();
	bool doesSubsume();
};

#endif /* GOTO_BALL_H_ */
