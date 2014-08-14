#include "RobotRightArm.h"


RobotRightArm::RobotRightArm()
{
	Elbow = new Servo(7, 5, 1); //intialize servo by setting Dynamixel ID, COMPORTNUM,BAUD RATE
	Shoulder = new Servo(5, 5, 1);
	armTwist = new Servo(6, 5, 1);
	Gripper = new Servo(8, 5, 1);

	//Note servos do not have overload management, so if you have a bracket and try to set an unreachable angel without setting limits, the servo will most definitely go to overload
	Elbow->setAngleLimits(202, 822);
	Shoulder->setAngleLimits(202, 822);
	armTwist->setAngleLimits(202, 822);
	Gripper->setAngleLimits(202, 822);
}


RobotRightArm::~RobotRightArm()
{
}


bool RobotRightArm::setCurrentParameters()
{
	Elbow->setCurrentParameters();
	Shoulder->setCurrentParameters();
	armTwist->setCurrentParameters();
	Gripper->setCurrentParameters();
	return true;
}

bool RobotRightArm::isMoving()
{
	if (Shoulder->isMoving() || armTwist->isMoving() || Elbow->isMoving() || Gripper->isMoving())
	{
		return true;
	}
	else
		return false;
}