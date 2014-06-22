#include "Servo.h"


Servo::Servo(int minimumLimit, int maximumLimit)
{
	minLimit = minimumLimit;
	maxLimit = maximumLimit;
}

Servo::Servo()
{
}

Servo::~Servo()
{
}

bool Servo::setPosition(int position, int speed)
{
	return true;
}
bool Servo::isMoving()
{
	return true;
}
bool Servo::setCurrentParameters()
{
	return true;
}

void Servo::enabletorque(bool enable)
{

}