//We used ciska's code for image processing, used session_04 code;

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include "avaraging.h"
#include "sine.h"



#define REDMASK	(0xff0000)
#define GREENMASK (0x00ff00)
#define BLUEMASK (0x0000ff)

using namespace cv;
using namespace std;

typedef unsigned int uint;

int main (int argc, char **argv){
    Mat camera;
    Mat gray_camera;
    Mat edges;
    Mat gray;
    Avaraging avarage(44100);
    Sine sine(1,44100);
    namedWindow("display window");
    VideoCapture cap (0);

    vector<Vec4i> lines;

    while(true){
      cap >> camera;

      // Read the camera as gray-scale
      cvtColor(camera, gray_camera , COLOR_BGR2GRAY);
      
      // egde detection
      Canny(gray_camera, edges, 1, 200);
      
      // detect lines trough points
      HoughLinesP(edges, lines, 1, CV_PI/180, 50, 50, 200);
      
      // Draw lines on the camera
      for (size_t i=0; i<lines.size(); i++) {
          Vec4i l = lines[i];
          line(camera, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255, 230, 10), 3, 1);
      }   
      
      for (float i = 0; i < 44100; i++){
          float value = avarage.smooth(sine.genNextSample());
      }

      imshow("Result camera", camera);
      waitKey(25);
    }
    return 0;
}


