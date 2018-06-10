/*
 * goto_ball.cpp
 *
 *  Created on: Apr 20, 2013
 *      Author: okan
 */

#include "goto_ball.h"
#include <math.h>

GotoBall::GotoBall() {
}

GotoBall::~GotoBall() {
}

void GotoBall::init()
{

}

void GotoBall::run()
{
	subsumption = false;

	if (generalSensorHelper->imageHelper.isBallKnown) {
		subsumption = true;

		int centerx =  generalSensorHelper->imageHelper.centerx;
		int centery = generalSensorHelper->imageHelper.centery;

		// according to balls position on the image generate wheel command to go the ball.
		// hint: consider deviation of the ball from the center of the image
		action.forwardCommand = 1;
		action.turnCommand = 0.4*(centerx-160)/320; //27
	}
}
