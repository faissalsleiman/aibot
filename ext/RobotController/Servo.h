#pragma once
class Servo
{
	int position, load, speed, temperature;
	int minLimit, maxLimit;

public:
	Servo(int minimumLimit, int maximumLimit);
	Servo();
	~Servo();
	bool setPosition(int position, int speed); //set a target position and specify speed of movement
	bool isMoving(); //returns true if the servo is currently moving
	bool setCurrentParameters(); //Polls the servo and sets the variables position, load, speed, temperature
	void enabletorque(bool enable); //if true will enable torque in the servo
};

