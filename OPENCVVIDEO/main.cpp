//We used ciska's code for image processing, used session_04 code;
// code is taken from https://learnopencv.com/find-center-of-blob-centroid-using-opencv-cpp-python/ , and altered by Rahsaan Bleijs 2022



#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#define REDMASK	(0xff0000)
#define GREENMASK (0x00ff00)
#define BLUEMASK (0x0000ff)

using namespace cv;
using namespace std;

typedef unsigned int uint;

#include "centroidDetection.h"

int main (int argc, char **argv){
  Mat camera;
  VideoCapture cap(0);

  CentroidDetection detect;
  
while(true){
  cap >> camera;
  detect.drawPoints(camera);



//=======================================
      // Moments m = moments(gray_camera,true);
      // Point p(m.m10/m.m00, m.m01/m.m00);
      // cout<< Mat(p)<< endl;
      
      // // cv.circle(img,(447,63), 63, (0,0,255), -1)
      // circle(camera, p, 5, Scalar(255,0,0), -1);
//=======================================

      //display the camara inside the window
      imshow("Display window", camera);


      //display time of the webcam frames
      waitKey(25);
        // return(0);
      }
    }
