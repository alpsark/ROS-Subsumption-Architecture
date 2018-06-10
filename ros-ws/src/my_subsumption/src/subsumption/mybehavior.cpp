/*
 * mybehavior.cpp
 *
 *  Created on: Apr 20, 2013
 *      Author: okan
 */

#include "mybehavior.h"

MyBehavior::MyBehavior() {

}

MyBehavior::~MyBehavior() {

}

bool MyBehavior::doesSubsume()
{
	return subsumption;
}

void MyBehavior::setGeneralSensorHelper(GeneralSensorHelper* _generalSensorHelper)
{
	generalSensorHelper = _generalSensorHelper;
}

MyAction MyBehavior::getAction()
{
	return action;
}
