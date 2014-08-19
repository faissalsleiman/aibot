#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
 
#include <iostream>
#include <stdio.h>

#include <ctime>
#include <chrono>

using namespace std;
using namespace cv;

int CAPTUREWIDTH = 640; //in pixels
int CAPTUREHEIGHT = 480; //in pixels
 
double getFaceDistance(int faceWidth, int faceHeight)
{
	return ((double)CAPTUREWIDTH/ faceWidth) * (double)18;

	//FORMULA: f = d*Z / D
	//d = faceWidth in Pixels
	//Z = Distance to Face
	//D = Actual Face Width
	//f = Capture Width in Pixels
}

int main(int argc, const char** argv)
{
	

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
    while(true)
    {
		//Start Timer
		auto start = std::chrono::high_resolution_clock::now();

        //capture a new image frame
        captureDevice>>captureFrame;

        //convert captured image to gray scale and equalize
        cvtColor(captureFrame, grayscaleFrame, CV_BGR2GRAY);
        equalizeHist(grayscaleFrame, grayscaleFrame);
 
        //create a vector array to store the face found
        std::vector<Rect> faces;
 
        //find faces and store them in the vector array
        face_cascade.detectMultiScale(grayscaleFrame, faces, 1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT|CV_HAAR_SCALE_IMAGE, Size(35,35));
		
 
        //draw a rectangle for all found faces in the vector array on the original image
        for(int i = 0; i < faces.size(); i++)
        {
            Point pt1(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
            Point pt2(faces[i].x, faces[i].y);

            rectangle(captureFrame, pt1, pt2, cvScalar(0, 255, 0, 0), 1, 8, 0);
			cout<<"FACE DETECTED: " << faces.size() <<endl;
			cout << "Face Size in Pixels: " << faces[i].width << "x" << faces[i].height << endl;
			cout << "Center of FACE Coordinates: " << faces[i].x + (faces[i].width / 2) << "," << faces[i].y + (faces[i].height / 2) << endl;
			cout << "Shift from Center of Camera: " << faces[i].x + (faces[i].width / 2) - (CAPTUREWIDTH / 2) << "," << faces[i].y + (faces[i].height / 2) - (CAPTUREWIDTH/2) << endl; //assuming 640x480 res. so center of the image is at 320,240. 
			cout << "Approx. Distance in cm: " << getFaceDistance(faces[i].width,faces[i].height) << endl;
        }
 
        //print the output
        imshow("outputCapture", captureFrame);
 
		//measure duration to run face detection and computing and print it
		auto elapsed = std::chrono::high_resolution_clock::now() - start;
		long long microseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
		cout << "TIME: " << microseconds;

        //pause for X-ms
        waitKey(100);
    }
 
    return 0;
}


