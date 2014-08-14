#include "Servo.h"

#pragma once
class RobotTorso
{
public:
	int x, y; //values relative to (0,0) which is the camera position
	Servo *panServo;
	Servo *tiltServo;

	RobotTorso();
	~RobotTorso();
	bool setPosition(int x, int y); //not implemented yet
	bool setCurrentParameters(); //Sets all the parameters of the servos to their current parameters (polled) so they can be retrieved directly

};

