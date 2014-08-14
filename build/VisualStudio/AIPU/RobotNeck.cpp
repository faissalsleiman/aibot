#include "RobotNeck.h"


RobotNeck::RobotNeck()
{

	panServo = new Servo(20, 5, 1); //intialize servo by setting Dynamixel ID, COMPORTNUM,BAUD RATE
	tiltServo = new Servo(21, 5, 1);

	//Note servos do not have overload management, so if you have a bracket and try to set an unreachable angel without setting limits, the servo will most definitely go to overload
	panServo->setAngleLimits(202, 822); 
	tiltServo->setAngleLimits(202, 822);
	
	
}


RobotNeck::~RobotNeck()
{
}


bool RobotNeck::setCurrentParameters()
{
	panServo->setCurrentParameters();
	tiltServo->setCurrentParameters();
	return true;
}