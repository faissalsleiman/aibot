#include "RobotMotionBase.h"


RobotMotionBase::RobotMotionBase()
{

	LeftWheel = new Servo(30, 5, 1); //intialize servo by setting Dynamixel ID, COMPORTNUM,BAUD RATE
	RightWheel = new Servo(31, 5, 1);

	LeftWheel->setAngleLimits(0, 0);
	RightWheel->setAngleLimits(0, 0);
}


RobotMotionBase::~RobotMotionBase()
{
}


bool RobotMotionBase::setCurrentParameters()
{
	LeftWheel->setCurrentParameters();
	RightWheel->setCurrentParameters();
	return true;
}