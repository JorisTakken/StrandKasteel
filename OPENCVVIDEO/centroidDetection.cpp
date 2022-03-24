#include "centroidDetection.h"

CentroidDetection::CentroidDetection(){
}

CentroidDetection::~CentroidDetection(){
    // delete mu;
    // delete mc;
    // mu = nullptr;
    // mc = nullptr;
}


void CentroidDetection::binaryImage(Mat& camera){
    cvtColor(camera, gray_camera, COLOR_BGR2GRAY);
    int h = gray_camera.rows;
    int w = gray_camera.cols;
    cout << h<< endl;


    for(int i = 0; i < h; i++) {
        uchar* row = gray_camera.ptr<uchar>(i);
        for(int j = 0; j < w; j++) {
            row[j] = row[j] > 80 ? 0 : 255;
        }
    }
}

void CentroidDetection::edgeDetection(){
    // make canny output (edge detection)
    Canny(gray_camera, canny_output, 100, 500,3);
}

void CentroidDetection::findingcontours(){
    findContours(canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
    cout << contours.size() << endl;

    
}   

void CentroidDetection::makePoints(){
    // make points 

    // std::vector<int> arr = std::vector<int> (20);
    mu = vector<Moments>(contours.size());
    mc = vector<Point2f>(contours.size());

    // mu(contours.size());
    // mc(contours.size()); 

    for( int i = 0; i<contours.size(); i++ ){ 
      mu[i] = moments(contours[i], false ); 
    }
    // get the centroid of figures with formula
    for( int i = 0; i<contours.size(); i++){ 
      mc[i] = Point2f(mu[i].m10/(mu[i].m00 + 1e-5 ), mu[i].m01/(mu[i].m00 + 1e-5)); 
    }
}

void CentroidDetection::drawPoints(Mat& camera){
    binaryImage(camera);
    edgeDetection();
    findingcontours();
    makePoints();

    Mat drawing(canny_output.size(), CV_8UC3, Scalar(255,255,255));
    for( int i = 0; i<contours.size(); i++ ){
      Scalar color = Scalar(167,151,111); // B G R values
      drawContours(camera, contours, i, color, 2, 8, hierarchy, 0, Point());
      circle(camera, mc[i], 5, Scalar(0,0,0), -1, 8, 0);
      std::cout << mc[i] << std::endl;
    }
}