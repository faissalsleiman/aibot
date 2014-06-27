// Windows version
#include <iostream>
#include <windows.h> //this is only here for the sleep function (testing purposes)
#include "Servo.h"

using namespace std;

int i;

int main()
{
	cout << "HELLO World, I am a ROBOT!!" << endl;

	Servo *testServo1 = new Servo(1, 5, 1);
	Servo *testServo2 = new Servo(1, 5, 1);


	//Note servos do not have overload management, so if you have a bracket and try to set an unreachable angel without setting limits, the servo will most definitely go to overload
	testServo1->setAngleLimits(256, 768);
	testServo1->setPosition(1023, 512); //;1023 will never be achieved, it will only go to the limit.
	do
	{
		testServo1->setCurrentParameters();
		cout << "Current (Position,Speed,Load,Temperature): (";
		cout << testServo1->position;
		cout << "," << testServo1->speed;
		cout << "," << testServo1->load;
		cout << "," << testServo1->temperature << ")" << endl;
		cout << "Comm Status: " << testServo1->checkCommStatus() << endl;
	} while (testServo1->isMoving());


	//Sleep(3000);

	cout << "**" << endl;
	testServo2->setAngleLimits(256, 768);
	testServo2->setPosition(0, 512);
	do
	{
		testServo2->setCurrentParameters();
		cout << "Current (Position,Speed,Load,Temperature): (";
		cout << testServo2->position;
		cout << "," << testServo2->speed;
		cout << "," << testServo2->load;
		cout << "," << testServo2->temperature << ")" << endl;
		cout << "Comm Status: " << testServo2->checkCommStatus() << endl;
	} while (testServo2->isMoving());


	cout << "Press any key to exit" << endl;
	cin >> i;
	delete testServo1;
	delete testServo2;

	return 0;
}

