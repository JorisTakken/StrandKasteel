#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

#define W 100
#define H 100

using namespace cv;

int main(){
    std::string image_path = samples::findFile("/Users/joristakken/Documents/StrandKasteel/detectImage/first_test/concreteContrast.png");
    Mat img = imread(image_path, IMREAD_COLOR);
        if(img.empty()){
            std::cout << "Could not read the image: " << image_path << std::endl;
            return 1;
        }
    // show Image
    imshow("Display window", img);
    int k = waitKey(0); // Wait for a keystroke in the window

        if(k == 's'){
            imwrite("starry_night.png", img);
        }
        return 0;
}

// int main( int argc, char **argv ){
//     // create array to store pixels, set all pixels to 0
//     uchar* buffer = new uchar[H * W];

    
//     memset(buffer, 0, sizeof(uchar) * H * W );

//     logValues(buffer, 0, 0, W, H);

//     #if 0
//     buffer[0] = (uchar)255;

//     #else
//         // loop through bytes
//         for(int i = 0; i < H; i++) {
//         int yOffset = i * W;
//         std::cout << "\n";
//         for(int j = 0; j < W; j++) {
//             float yValue = (float)(i + 1) / H; //range van 0 - 1
//             float xValue = (float)(j + 1) / W; //persentage!
//             buffer[j + yOffset] = (uchar)(255.0f * yValue *  xValue);
//         }
//         }
//     #endif

//     logValues(buffer, 0, 0, W, H);

//     // CV_8UC4
//     // format: CV_<bit-depth>{U|S|F}C(<number_of_channels>)
//     // CV_8UC4 results in: 8-bit unsigned integer matrix/image with 4 channel 
//     // NOTE: opencv first place rows, then columns
//     Mat img = Mat( H, W, CV_8UC1, buffer);

//     // log first 10x10 values in matrix --> all 0
//     logValues(img, 0, 0, W, H);


//     // ==========  show result ==========
//     // scale image
//     float scaleFactor = 100.0f;
//     cv::resize(img, img, Size(), scaleFactor, scaleFactor, INTER_NEAREST);
//     // create window and image matrix
//     char window[] = "Drawing 2D";
//     namedWindow( window, WINDOW_AUTOSIZE );
//     imshow(window, img);
//     waitKey( 0 );
//     return 0;
// }