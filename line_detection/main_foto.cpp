//We used ciska's code for image processing, used session_04 code;

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include "writeToFile.h"

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
    Mat gray_image;
    Mat edges;
    Mat gray;

    vector<Vec4i> lines;
    // read image
    image = imread( imageName, IMREAD_COLOR);
    // Read the image as gray-scale
    cvtColor(image, gray_image , COLOR_BGR2GRAY);
    Canny(gray_image, edges, 50, 200);
    HoughLinesP(edges, lines, 1, CV_PI/180, 10, 50, 200);

    // Draw lines on the image


    WriteToFile fileWriter("X_Y_values_lines.csv", true);

    for (size_t i=0; i<lines.size(); i++) {
        Vec4i l = lines[i];
        line(image, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255, 230, 10), 3, LINE_AA);
        fileWriter.write(" x " + std::to_string(l[0]) + " y " + std::to_string(l[1]) + " x2 " + std::to_string(l[2]) + " y2 " + std::to_string(l[3]) + "\n");


    } 
    imshow("Result Image", image);
    waitKey(0);
}