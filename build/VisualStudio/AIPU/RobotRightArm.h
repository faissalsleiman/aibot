#include "Servo.h"
#include "ForceSensor.h"

#pragma once
class RobotRightArm
{

public:
	Servo *Elbow;
	Servo *Shoulder;
	Servo *armTwist;
	Servo *Gripper;
	ForceSensor *fingerSensor;

	RobotRightArm();
	~RobotRightArm();
	bool setPosition(int x, int y);
	bool Wave();
	bool setCurrentParameters(); //Sets all the parameters of the servos to their current parameters (polled) so they can be retrieved directly
	bool isMoving();

};

