/*
 * myarbitrator.cpp
 *
 *  Created on: Apr 20, 2013
 *      Author: okan
 */

#include "myarbitrator.h"

MyArbitrator::MyArbitrator(GeneralSensorHelper* _generalSensorHelper) {
	generalSensorHelper = _generalSensorHelper;
}

MyArbitrator::~MyArbitrator() {
}

void MyArbitrator::addBehavior(MyBehavior* behavior)
{
	behaviors.push_back(behavior);

	behavior->setGeneralSensorHelper(generalSensorHelper);
	behavior->init();
}

void MyArbitrator::run()
{
	action.turnCommand = 0;
	action.forwardCommand = 0;
	// iterate over all behaviors starting from the level 0.
	for (int i = 0; i < behaviors.size(); i++)
	{
		behaviors[i]->run();
		if (behaviors[i]->doesSubsume()) {
			action = behaviors[i]->getAction();
			std::cout << "Level " << i << std::endl ;
			if(i == 1){
				behaviors[2]->run(); 	
			} 
			break;
		}
	}
}

MyAction MyArbitrator::getAction()
{
	return action;
}
