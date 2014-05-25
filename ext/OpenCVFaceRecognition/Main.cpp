#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
 
#include <iostream>
#include <stdio.h>
 
using namespace std;
using namespace cv;
 
double getFaceDistance(int faceWidth, int faceHeight)
{
	double invertedarea = 1.0 - ((faceWidth*faceHeight) / (double)(640 * 480));
	if (invertedarea == 0.5)
	{
		return 1.0;
	}
	if (invertedarea < 0.5)
	{
		return 1.0 - invertedarea;
	}
	if (invertedarea > 0.5)
	{
		return 1.0 + invertedarea;
	}
	return -1;
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
 
    //setup image files used in the capture process
    Mat captureFrame;
    Mat grayscaleFrame;
 
    //create a window to present the results
    namedWindow("outputCapture", 1);
 
    //create a loop to capture and find faces
    while(true)
    {
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
			cout << "FACE Coordinates: " << faces[i].x << "," << faces[i].y << endl;
			cout<<"FACE DIMENTIONS: " <<faces[i].width << "x" << faces[i].height <<endl;
			cout << "Distance in Meters: " << getFaceDistance(faces[i].width,faces[i].height) << endl;
        }
 
        //print the output
        imshow("outputCapture", captureFrame);
 
        //pause for 33ms
        waitKey(330);
    }
 
    return 0;
}