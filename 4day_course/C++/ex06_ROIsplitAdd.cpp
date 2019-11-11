#include "OpenCV_Functions.h"

using namespace std;
using namespace cv;

int main(void){
    int i, j;
    string name = path_to_images();
    Mat image = imread(name);
  namedWindow("image",WINDOW_GUI_EXPANDED); imshow("image",image); waitKey();
    int w = image.cols;
    int h = image.rows;

    vector<Point> points;
    points.push_back(Point(int(w*0.35),int(h*0.65)));
    points.push_back(Point(int(w*0.65),int(h*0.65)));
    points.push_back(Point(int(w*1.00),int(h*1.00)));
    points.push_back(Point(int(w*0.00),int(h*1.00)));
    
    Mat active, deactive, HLS, white, yellow, result;
    polyROI(image, active, points);
    deactive = image - active;
    namedWindow("active",WINDOW_GUI_EXPANDED); 
    imshow("active",active); waitKey();
    namedWindow("deactive",WINDOW_GUI_EXPANDED); 
    imshow("deactive",deactive); waitKey();

    Scalar whiteLower(0,200,0);
    Scalar whiteUpper(179,255,255);
    Scalar yellowLower(15,30,115);
    Scalar yellowUpper(35,204,255);

    cvtColor(active, HLS, COLOR_BGR2HLS);
    splitColor(HLS, white, whiteLower, whiteUpper);
    splitColor(HLS, yellow, yellowLower, yellowUpper);
    HLS = white+yellow;
    cvtColor(HLS, active, COLOR_HLS2BGR);

    namedWindow("Split",WINDOW_GUI_EXPANDED); 
    imshow("Split",active); waitKey();

    addWeightedImage(active, deactive, result, 100, 100);
    namedWindow("result",WINDOW_GUI_EXPANDED); 
    imshow("result",result); waitKey();


    return 0;
}
