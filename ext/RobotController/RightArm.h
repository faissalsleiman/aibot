#include "Servo.h"
#include "ForceSensor.h"

#pragma once
class RightArm
{
	Servo Elbow;
	Servo Shoulder;
	Servo armTwist;
	Servo Gripper;
	ForceSensor fingerSensor;

public:
	RightArm();
	~RightArm();
	bool setPosition(int x, int y);
	bool Wave();

};

