/*
 * myarbitrator.h
 *
 *  Created on: Apr 20, 2013
 *      Author: okan
 */

#ifndef MYARBITRATOR_H_
#define MYARBITRATOR_H_

#include "mybehavior.h"
#include <vector>
#include "myaction.h"

#include "../general_sensor_helper.h"

class MyArbitrator {

private:
	std::vector<MyBehavior*> behaviors;
	MyAction action;

	// general sensor helper module
	GeneralSensorHelper* generalSensorHelper;

public:
	MyArbitrator(GeneralSensorHelper* _generalSensorHelper);
	virtual ~MyArbitrator();

	void addBehavior(MyBehavior* behavior);
	void run();
	MyAction getAction();
};

#endif /* MYARBITRATOR_H_ */
