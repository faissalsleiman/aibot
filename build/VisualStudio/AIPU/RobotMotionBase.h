#include "Servo.h"

#pragma once
class RobotMotionBase
{
public:
	int x, y; //values relative to (0,0) which is the camera position
	Servo *LeftWheel;
	Servo *RightWheel;


	RobotMotionBase();
	~RobotMotionBase();
	bool setPosition(int x, int y); //not implemented yet
	bool setCurrentParameters(); //Sets all the parameters of the servos to their current parameters (polled) so they can be retrieved directly

};

