#include "Servo.h"

#pragma once
class RobotNeck
{
public:
	int x, y; //values relative to (0,0) which is the camera position
	Servo *panServo;
	Servo *tiltServo;


	RobotNeck();
	~RobotNeck();
	bool setPosition(int x, int y); //not implemented yet
	bool setCurrentParameters(); //Sets all the parameters of the servos to their current parameters (polled) so they can be retrieved directly
	bool nodYes(); //nods yes
	bool nodNo(); //nods no
};

