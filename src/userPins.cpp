#include "userPins.h"


userPins::userPins()
{
	
	
}


void userPins::draw(ofVec3f vecpos, int myradius)
{
	ofFill();
	ofDrawSphere(vecpos, myradius);

	PinPos = vecpos;

	radius = myradius;
}