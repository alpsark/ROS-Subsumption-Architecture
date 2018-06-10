/*
 * mybehavior.h
 *
 *  Created on: Apr 20, 2013
 *      Author: okan
 */

#ifndef MYBEHAVIOR_H_
#define MYBEHAVIOR_H_

#include "myaction.h"
#include "../general_sensor_helper.h"

class MyBehavior {
protected:
	MyAction action;
	GeneralSensorHelper* generalSensorHelper;
	bool subsumption;

public:
	MyBehavior();
	virtual ~MyBehavior();

	virtual void init() = 0;
	virtual void run() = 0;

	bool doesSubsume();
	void setGeneralSensorHelper(GeneralSensorHelper* _generalSensorHelper);
	MyAction getAction();
};

#endif /* MYBEHAVIOR_H_ */
