#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#pragma once

#define REDMASK	(0xff0000)
#define GREENMASK (0x00ff00)
#define BLUEMASK (0x0000ff)

using namespace cv;
using namespace std;

typedef unsigned int uint;

class CentroidDetection{
    public:
        CentroidDetection();
        ~CentroidDetection();

        void binaryImage(Mat& camera);
        void edgeDetection();
        void findingcontours();
        void makePoints();

        void drawBigCentroid(Mat& camera);
        void drawPoints(Mat& camera);

        vector<Moments>mu;
        vector<Point2f>mc;

    protected:
        Mat gray_camera;
        Mat canny_output;
        vector<vector<Point>> contours; //store contours into a vector of points (contours)
                                        // dubble array
        vector<Vec4i> hierarchy; //contains information about countour vector
       
  

};
