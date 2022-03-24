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
  char* imageName = argv[1];
  Mat image;
  image = imread(imageName, IMREAD_COLOR );

  Mat gray_camera;

  // make a gray image
  cvtColor(image, gray_camera, COLOR_BGR2GRAY);

  // make binary image
  int h = gray_camera.rows;
  int w = gray_camera.cols;

  for(int i = 0; i < h; i++) {
      uchar* row = gray_camera.ptr<uchar>(i);
      for(int j = 0; j < w; j++) {
        row[j] = row[j] > 80 ? 0 : 255;
        }
      }

    // make canny output (edge detection)
    Mat canny_output;
    Canny(gray_camera, canny_output, 100, 500,3);

    // find contrours
    vector<vector<Point>> contours; //store contours into a vector of points (contours)
                                    // dubble array
    vector<Vec4i> hierarchy; //contains information about countour vector
    findContours(canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

    // make points 
    vector<Moments> mu(contours.size());
    for( int i = 0; i<contours.size(); i++ ){ 
      mu[i] = moments(contours[i], false ); 
    }

    // get the centroid of figures with formula
    vector<Point2f> mc(contours.size());
    for( int i = 0; i<contours.size(); i++){ 
      mc[i] = Point2f(mu[i].m10/(mu[i].m00 + 1e-5), mu[i].m01/(mu[i].m00 + 1e-5)); 
    }

    // draw points
    Mat drawing(canny_output.size(), CV_8UC3, Scalar(255,255,255));
    for( int i = 0; i<contours.size(); i++ ){
        Scalar color = Scalar(167,151,111); // B G R values
        drawContours(image, contours, i, color, 2, 8, hierarchy, 0, Point());
        circle( image, mc[i], 5, Scalar(0,0,0), -1, 8, 0);
        std::cout << mc[i] << std::endl;
    }

    //display the image inside the window
    imshow("Display window", image);


    //display time of the webcam frames
    waitKey(0);
    return(0);
    }
