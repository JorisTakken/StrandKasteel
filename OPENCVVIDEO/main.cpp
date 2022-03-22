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

int main (int argc, char **argv){
  // char* imageName = argv[1];
  // Mat image;
  // image = imread(imageName, IMREAD_COLOR );
  Mat camera;
  Mat gray_camera;
  VideoCapture cap (0);
while(true){
  cap >> camera;
  cvtColor(camera, gray_camera, COLOR_BGR2GRAY);

      int h = gray_camera.rows;
      int w = gray_camera.cols;

      for(int i = 0; i < h; i++) {
        uchar* row = gray_camera.ptr<uchar>(i);
        for(int j = 0; j < w; j++) {
          row[j] = row[j] > 80 ? 0 : 255;

        }
      }

      Moments m = moments(gray_camera,true);
      Point p(m.m10/m.m00, m.m01/m.m00);
      cout<< Mat(p)<< endl;
      // cv.circle(img,(447,63), 63, (0,0,255), -1)
      circle(camera, p, 5, Scalar(255,0,0), -1);


      //display the image inside the window
      imshow("Display window", camera);


      //display time of the webcam frames
      waitKey(25);
        // return(0);
      }
    }
