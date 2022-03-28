#include <opencv2/opencv.hpp>


// This code was made with gthe help of https://www.selfmadetechie.com/how-to-create-a-webcam-video-capture-using-opencv-c


using namespace std;
using namespace cv;

int main()
{


    //Create an empty matrix
    Mat image;

    //make a window with name: display window
    namedWindow("display window");


    //initialize video, 0 = the index of the webcam
    VideoCapture cap (0);

    if(!cap.isOpened()) {

      cout << "cannot open camera";
    }

while(true) {

    //insert the webcame fram inside matrix
    cap >> image;

    //display the image inside the window
    imshow("Display window", image);


    //display time of the webcam frames
    waitKey(25);

  }




return 0 ;

}
