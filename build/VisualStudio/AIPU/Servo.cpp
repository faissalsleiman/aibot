#include <iostream>
#include "dynamixel/dynamixel.h"

#pragma comment(lib, "dynamixel.lib")

#include "Servo.h"

using namespace std;

// Control table address
// For details refer to http://support.robotis.com/en/techsupport_eng.htm#software/embeded_c/cm510_cm700.htm
#define P_CW_ANGEL_LIMIT		6
#define P_CCW_ANGEL_LIMIT		8
#define P_TORQUE_ENABLE			24
#define P_GOAL_POSITION			30
#define P_MOVING_SPEED			32
#define P_PRESENT_POSITION		36
#define P_PRESENT_SPEED			38
#define P_PRESENT_LOAD			40
#define P_PRESENT_TEMPERATURE	43
#define P_MOVING				46



// Defulat setting
#define DEFAULT_PORTNUM		5 // COM5
#define DEFAULT_BAUDNUM		1 // 1Mbps
#define DEFAULT_ID			1

Servo::Servo(int dynamixelIDtoSet, int COMPortNumber, int BaudRateinMbps)
{
	dynamixelID = dynamixelIDtoSet;
	if (dxl_initialize(COMPortNumber, BaudRateinMbps) == 0) //it is ok to do this with multiple servos
	{
		cout << "Failed to open USB2Dynamixel!\n" << endl;

	}
	else
		cout << "Succeed to open USB2Dynamixel!\n" << endl;
}

Servo::Servo()
{
	dynamixelID = DEFAULT_ID;
	if (dxl_initialize(DEFAULT_PORTNUM, DEFAULT_BAUDNUM) == 0) //it is ok to do this with multiple servos
	{
		cout << "Failed to open USB2Dynamixel!\n" << endl;

	}
	else
		cout << "Succeed to open USB2Dynamixel!\n" << endl;

}

Servo::~Servo()
{
	cout << "terminating connection" << endl;
	dxl_terminate();
}

bool Servo::setPosition(int position, int speed)
{
	dxl_write_word(dynamixelID, P_MOVING_SPEED, speed); 
	dxl_write_word(dynamixelID, P_GOAL_POSITION, position);
	return true;
}

bool Servo::setRotationSpeed(int speed, wheelRotationDirection direction)
{
	//dynamixel wheels when given a speed 0-1024 will rotate CCW. when give between 1024 -2047 it will rotate counterclockwise
	if (direction == wheelRotationDirection::CW) 
	{
		dxl_write_word(dynamixelID, P_MOVING_SPEED, speed+1024);
	}
	else
	{
		dxl_write_word(dynamixelID, P_MOVING_SPEED, speed);
	}
	
	return true;
}
bool Servo::setAngleLimits(int ClockwiseAngle, int CounterClockwiseAngle)
{
	dxl_write_word(dynamixelID, P_CW_ANGEL_LIMIT, ClockwiseAngle);
	dxl_write_word(dynamixelID, P_CCW_ANGEL_LIMIT, CounterClockwiseAngle);
	return true;
}
bool Servo::isMoving()
{
	return  dxl_read_byte(dynamixelID, P_MOVING);
}
bool Servo::setCurrentParameters()
{
	position = dxl_read_word(dynamixelID, P_PRESENT_POSITION);
	speed = dxl_read_word(dynamixelID, P_PRESENT_SPEED);
	load = dxl_read_word(dynamixelID, P_PRESENT_LOAD);
	temperature = dxl_read_word(dynamixelID, P_PRESENT_TEMPERATURE);
	return true;
}

bool Servo::checkCommStatus()
{
	int commStatus = dxl_get_result();

	switch (commStatus)
	{
	case COMM_RXSUCCESS:
		return true;
		break;

	case COMM_TXFAIL:
		printf("COMM_TXFAIL: Failed transmit instruction packet!\n");
		break;

	case COMM_TXERROR:
		printf("COMM_TXERROR: Incorrect instruction packet!\n");
		break;

	case COMM_RXFAIL:
		printf("COMM_RXFAIL: Failed get status packet from device!\n");
		break;

	case COMM_RXWAITING:
		printf("COMM_RXWAITING: Now recieving status packet!\n");
		break;

	case COMM_RXTIMEOUT:
		printf("COMM_RXTIMEOUT: There is no status packet!\n");
		break;

	case COMM_RXCORRUPT:
		printf("COMM_RXCORRUPT: Incorrect status packet!\n");
		break;

	default:
		printf("This is unknown error code!\n");
		break;
	}
	return false;
}
void Servo::enabletorque(bool enable)
{
	//note that if you disable torque then set positiion, that would automatically set the torque to on
	dxl_write_word(dynamixelID, P_TORQUE_ENABLE, enable);
}



/*
// Print error bit of status packet
void PrintErrorCode()
{
if (dxl_get_rxpacket_error(ERRBIT_VOLTAGE) == 1)
printf("Input voltage error!\n");

if (dxl_get_rxpacket_error(ERRBIT_ANGLE) == 1)
printf("Angle limit error!\n");

if (dxl_get_rxpacket_error(ERRBIT_OVERHEAT) == 1)
printf("Overheat error!\n");

if (dxl_get_rxpacket_error(ERRBIT_RANGE) == 1)
printf("Out of range error!\n");

if (dxl_get_rxpacket_error(ERRBIT_CHECKSUM) == 1)
printf("Checksum error!\n");

if (dxl_get_rxpacket_error(ERRBIT_OVERLOAD) == 1)
printf("Overload error!\n");

if (dxl_get_rxpacket_error(ERRBIT_INSTRUCTION) == 1)
printf("Instruction code error!\n");
}
*/