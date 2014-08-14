#pragma once

enum wheelRotationDirection { //Used only when servo is in wheel mode
	CW = 0,
	CCW,
};


class Servo
{
	//hello

public:
	int dynamixelID;
	int position, load, speed, temperature;
	int minLimit, maxLimit;

	Servo(int dynamixelID, int COMPortNumber, int BaudRateinMbps);
	Servo();
	~Servo();
	bool setPosition(int position, int speed); //set a target position and specify speed of movement
	bool setRotationSpeed(int speed, wheelRotationDirection direction); //sets a target speed of rotation, this is used when it is operated as a wheel
	bool setAngleLimits(int ClockwiseAngle, int CounterClockwiseAngle); //set a turning CW and CCW limits
	bool isMoving(); //returns true if the servo is currently moving
	bool setCurrentParameters(); //Polls the servo and sets the variables position, load, speed, temperature
	bool checkCommStatus(); //returns true if communication is successfull
	void enabletorque(bool enable); //if true will enable torque in the servo. Note that if you disable torque then set positiion, that would automatically set the torque to on
};

