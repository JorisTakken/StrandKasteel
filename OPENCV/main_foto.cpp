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
    if(argv[1] == NULL) {
      std::cout << "\nPlease add a path to an image when running this program!\n\n";
      return 0;
    }
    char* imageName = argv[1];

    Mat image;
    // read image
    image = imread( imageName, IMREAD_COLOR);

    // Mat image;
    Mat gray_image;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    cvtColor(image, gray_image, COLOR_BGR2GRAY);

    findContours(gray_image, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

    int idx = 0;
    for ( ; idx >= 0; idx = hierarchy[idx][0]){
        
        // Scalar color(rand()&255,rand()&255,rand()&255);
        drawContours(gray_image,contours,idx,255,100,8,hierarchy);
            
        }
        //display the image inside the window
        imshow("Display window", gray_image);


        //display time of the webcam frames
        waitKey(0);

      // }

    return(0);
}
