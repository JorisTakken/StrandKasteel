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
        void listGen();

        float getParam1();
        float getParam2();
        float getParam3();
        float getParam4();
        float getParam5();

        float getParam6();
        float getParam7();
        float getParam8();
        float getParam9();
        float getParam10();

        float getBigParam();

        vector<Moments>mu;
        vector<Point2f>mc; // centroid point [x,y]


        vector<float>xValues;
        vector<float>yValues;


        float *xFloats;
        float x;
        float y;

        float paramUnscaled[11] = {0,0,0,0,0,0,0,0,0,0,0};


    protected:
        Mat gray_camera;
        Mat canny_output;
        vector<vector<Point>> contours; //store contours into a vector of points (contours)
                                        // dubble array
        vector<Vec4i> hierarchy; //contains information about countour vector

};
