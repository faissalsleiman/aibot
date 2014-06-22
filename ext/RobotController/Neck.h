#include "Servo.h"

#pragma once
class Neck
{
	int x, y; //values relative to (0,0) which is the camera position
	Servo tiltServo;
	Servo panServo;

public:
	Neck();
	~Neck();
	bool setPosition(int x, int y); 
	bool setCurrentParameters(); //Sets the values of x and y

};

