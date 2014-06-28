// Windows version
#include <iostream>
#include <windows.h> //this is only here for the sleep function (testing purposes)
#include "Servo.h"


#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;
using namespace cv;

int CAPTUREWIDTH = 640; //in pixels
int CAPTUREHEIGHT = 480; //in pixels
double XCAPTUREVIEWINGANGLE = 60;
double YCAPTUREVIEWINGANGLE = 45;

double getFaceDistance(int faceWidth, int faceHeight)
{
	return ((double)CAPTUREWIDTH / faceWidth) * (double)18;

	//NOTE: if a new camera is used, the formula must be re-calibrated
	//FORMULA: f = d*Z / D
	//d = faceWidth in Pixels
	//Z = Distance to Face
	//D = Actual Face Width
	//f = Capture Width in Pixels
}


int main(int argc, const char** argv)
{
	Servo *testServo1 = new Servo(2, 5, 1);
	testServo1->setAngleLimits(202, 822);
	testServo1->setPosition(512, 128);

	//create the cascade classifier object used for the face detection
	CascadeClassifier face_cascade;
	//use the haarcascade_frontalface_alt.xml library
	face_cascade.load("..\\..\\..\\config\\Opencv\\haarcascade_frontalface_alt.xml");

	//setup video capture device and link it to the first capture device
	VideoCapture captureDevice;

	captureDevice.open(0);
	//Set Dimensions
	captureDevice.set(CV_CAP_PROP_FRAME_HEIGHT, CAPTUREHEIGHT);
	captureDevice.set(CV_CAP_PROP_FRAME_WIDTH, CAPTUREWIDTH);

	//setup image files used in the capture process
	Mat captureFrame;
	Mat grayscaleFrame;

	//create a window to present the results
	namedWindow("outputCapture", 1);

	//create a loop to capture and find faces
	while (true)
	{
		//capture a new image frame
		captureDevice >> captureFrame;

		//convert captured image to gray scale and equalize
		cvtColor(captureFrame, grayscaleFrame, CV_BGR2GRAY);
		equalizeHist(grayscaleFrame, grayscaleFrame);

		//create a vector array to store the face found
		std::vector<Rect> faces;

		//find faces and store them in the vector array
		face_cascade.detectMultiScale(grayscaleFrame, faces, 1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT | CV_HAAR_SCALE_IMAGE, Size(35, 35));


		//draw a rectangle for all found faces in the vector array on the original image
		for (int i = 0; i < faces.size(); i++)
		{
			Point pt1(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
			Point pt2(faces[i].x, faces[i].y);

			rectangle(captureFrame, pt1, pt2, cvScalar(0, 255, 0, 0), 1, 8, 0);

			/*
			STEPS FOR CALCULATING ANGLE SHIFT for Servo Motor
			1-getFaceDistance() function must be calibrated to get an accurate measurement of planar distance to the face
			2-Shift from center camera must be converted to cm using this formula
			Shift in cm = (tan(camera viewing angle/2) x (planar distance to face in cm) ) x Center ShiftX / (CAPTUREWIDTH/2)
			3-atan(Shift from center / planar distance to face) will give us the angle shift
			NOTE: this result will be in radian
			4-position to set the servo to must be set using the following formula (assuming 512 is center position)
			position to set = (angle calculated in step3 / 1.57) x (unsigned additional servo int value at a 90degree angle) + 512
			the value representa 90degrees converted to radian
			*/
			
			//CALCULATIONS STEP 1
			cout << "FACE DETECTED: " << faces.size() << endl;
			cout << "Face Size in Pixels: " << faces[i].width << "x" << faces[i].height << endl;
			cout << "Center of FACE Coordinates: " << faces[i].x + (faces[i].width / 2) << "," << faces[i].y + (faces[i].height / 2) << endl;
			double centerShiftX = -(faces[i].x + (faces[i].width / 2) - (CAPTUREWIDTH / 2));
			double centerShiftY = -(faces[i].y + (faces[i].height / 2) - (CAPTUREHEIGHT / 2));
			cout << "Shift from Center of Camera: " << centerShiftX << "," << centerShiftY << endl; //assuming 640x480 res. so center of the image is at 320,240. 
			double planarFaceDistance = getFaceDistance(faces[i].width, faces[i].height);
			cout << "Approx. Distance in cm: " << planarFaceDistance << endl;

			
			//CALCULATIONS STEP 2
			//note we are multiplying the angel by pi and divided by 180 because we need to work in radians
			double centerShiftXinCM = tan((XCAPTUREVIEWINGANGLE / 2) *3.14159265 / 180) * planarFaceDistance * centerShiftX / (CAPTUREWIDTH / 2);
			double centerShiftYinCM = tan((YCAPTUREVIEWINGANGLE / 2) *3.14159265 / 180) * planarFaceDistance * centerShiftY / (CAPTUREHEIGHT / 2);

			//CALCULATIONS STEP 3
			double angleShiftX = atan(centerShiftXinCM / planarFaceDistance);
			double angleShiftY = atan(centerShiftYinCM / planarFaceDistance);

			//CALCULATIONS STEP 4
			int XServoPositiontoSet = ((angleShiftX / 1.57) * 310 )+ 512;
			int YServoPositiontoSet = ((angleShiftY / 1.57) * 310) + 512;
			
			//Note servos do not have overload management, so if you have a bracket and try to set an unreachable angel without setting limits, the servo will most definitely go to overload
			testServo1->setPosition(YServoPositiontoSet, 128); //;1023 will never be achieved, it will only go to the limit.
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

		}

		//print the output
		imshow("outputCapture", captureFrame);

		//pause for X-ms
		waitKey(100);
	}

	return 0;
}





