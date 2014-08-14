#include "RobotLeftArm.h"


RobotLeftArm::RobotLeftArm()
{
	Elbow = new Servo(10, 5, 1); //intialize servo by setting Dynamixel ID, COMPORTNUM,BAUD RATE
	Shoulder = new Servo(11, 5, 1);
	armTwist = new Servo(12, 5, 1);
	Gripper = new Servo(13, 5, 1);

	//Note servos do not have overload management, so if you have a bracket and try to set an unreachable angel without setting limits, the servo will most definitely go to overload
	Elbow->setAngleLimits(202, 822);
	Shoulder->setAngleLimits(202, 822);
	armTwist->setAngleLimits(202, 822);
	Gripper->setAngleLimits(202, 822);
}


RobotLeftArm::~RobotLeftArm()
{
}

bool RobotLeftArm::setCurrentParameters()
{
	Elbow->setCurrentParameters();
	Shoulder->setCurrentParameters();
	armTwist->setCurrentParameters();
	Gripper->setCurrentParameters();
	return true;
}
