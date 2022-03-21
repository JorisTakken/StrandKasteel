//We used ciska's code for image processing, used session_04 code;




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
  Mat camera;
  Mat gray_camera;

  namedWindow("display window");
  VideoCapture cap (0);
  while(true) {

      //insert the webcame fram inside matrix
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

      //display the image inside the window
      imshow("Display window", gray_camera);


      //display time of the webcam frames
      waitKey(25);

    }

  return(0);
}
