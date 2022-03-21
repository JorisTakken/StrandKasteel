//We used ciska's code for image processing, used session_04 code;

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <vector>

#define REDMASK	(0xff0000)
#define GREENMASK (0x00ff00)
#define BLUEMASK (0x0000ff)

using namespace cv;
using namespace std;

typedef unsigned int uint;

int main (int argc, char **argv){
    // char* imageName = argv[1];
    // Mat image;
    Mat camera;
    Mat gray_camera;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;


    namedWindow("display window");
    VideoCapture cap (0);
    while(true) {
        //insert the webcame fram inside matrix
        cap >> camera;

        cvtColor(camera, gray_camera, COLOR_BGR2GRAY);

        findContours(gray_camera, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
        int idx = 0;
        for ( ; idx >= 0; idx = hierarchy[idx][0]){
          Scalar color(rand()&255,rand()&255,rand()&255);
          drawContours(gray_camera,contours,idx,color,FILLED,8,hierarchy);
            
        }
        //display the image inside the window
        imshow("Display window", gray_camera);


        //display time of the webcam frames
        waitKey(25);

      }

    return(0);
}
