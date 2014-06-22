#include <iostream>
#include "SerialClass.h"	// Library described above
#include <string>
#include <sstream>

using namespace std;

/*
HADI CONCLUSIONS FROM THIS TEST
Serial Data (in buffer) is sent out of sync. This is why we need to serialize it. For this reason, below I have implemented
that only 1 char is read at a time instead of the entire serial buffer. Arduino must send its packet within delimiters, in this
example our delimiters are '[' and  ']'.

Secondly, Timing in Serial communication is always out of sync becuase processing cycles in arduino and the PC are at different speeds.
As such, we cannot have a general c++ program that runs with a certain serial receiving loop and an arduino chip
that sends it data intermittently (for example 4 msgs within 5ms then 2 msgs within 100ms) this would be typical from 
sensor data that is triggered only when there is a change for example a force sensor.
As such, my conclusion is to run code in arduino and the PC at specific delay/loop times with raw sensor data always being 
pushed to the PC. All processing is to be done by the PC (for example the PC will detect if the force sensor is triggered 
and arduino only sends the PC the RAW data which might be 10000 cycles of 0V and 10 cycles of 5V).
The below delay in ms is to be adjusted in order to ensure all raw data sent by arduino is received in sync. The below 
number will most definitely only work with the processor I am currently running this test on. As such, it will need calibration
with another processor.
*/

// application reads from the specified serial port and reports the collected data
int main()
{
	cout << "Welcome to the serial test app!\n\n" << endl;

	Serial* SP = new Serial("COM4");    // adjust as needed

	if (SP->IsConnected())
		cout << "We're connected" << endl;


	int readResult = 0;
	char charReceived;
	char receiveBuffer[256] = "";
	bool streamOK = false;

	int counterNumber = 0; //this is a counter only to test if msgs received are in sync

	while (SP->IsConnected())
	{
		int indexOfBuffer = 0;
		streamOK = false;
		readResult = SP->ReadData(&charReceived, 1);

		if (readResult > 0)
		{
			if (charReceived == '[')
			{
				readResult = SP->ReadData(&charReceived, 1);
				while (charReceived != ']')
				{
					
					if (readResult == -1)
					{
						streamOK = false;
						break;
					}
					receiveBuffer[indexOfBuffer] = charReceived;
					indexOfBuffer++;
					streamOK = true;
					readResult = SP->ReadData(&charReceived, 1);
				}
			}
			if (streamOK == true)
			{
				string output(receiveBuffer,indexOfBuffer);  // Data Received in string OUTPUT!!

				string sensorName;
				string sensorValue;

				string delimiter = ",";
				
				size_t pos = 0;
				std::string token;
				if ((pos = output.find(delimiter)) != std::string::npos) {
					sensorName = output.substr(0, pos);
					output.erase(0, pos + delimiter.length());
					sensorValue = output;
				}
				

				if (atoi(sensorValue.c_str()) != (counterNumber + 1)) //beep if we missed a command (THIS IS FOR TESTING ONLY!!)
				{
					cout << '\a';
				}
				cout << "%" << sensorValue << "%" << endl;
				counterNumber = atoi(sensorValue.c_str());
				
			}
		}
			
		Sleep(25);
	} //end of while
	return 0;
}