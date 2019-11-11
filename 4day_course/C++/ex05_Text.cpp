#include "OpenCV_Functions.h"

using namespace std;
using namespace cv;

int main(void){
    int i, j;
    string name = path_to_images();
    Mat image = imread(name);
    Mat Line, Tri, Rec, Cir;
  namedWindow("image",WINDOW_GUI_EXPANDED); imshow("image",image); waitKey();
    int w = image.cols;
    int h = image.rows;

    vector<Point> points;
    points.push_back(Point(int(w*0.35),int(h*0.65)));
    points.push_back(Point(int(w*0.65),int(h*0.65)));
    points.push_back(Point(int(w*1.00),int(h*1.00)));
    points.push_back(Point(int(w*0.00),int(h*1.00)));
    drawPolygon(image,image,points,true,Scalar(255,0,0),5);
    namedWindow("Poly",WINDOW_GUI_EXPANDED); imshow("Poly",image); waitKey();

    drawText(image,image,"OpenCV Image",Point(10,50),FONT_HERSHEY_SIMPLEX,1.5,Scalar(0,255,0),3);
    namedWindow("Text",WINDOW_GUI_EXPANDED); imshow("Text",image); waitKey();

    drawEllipse(image,image,Point(int(w*0.5),int(h*0.5)),Size(130,130),0.0,0.0,360.0,Scalar(255,255,255),-1);
    namedWindow("Ellipse",WINDOW_GUI_EXPANDED); imshow("Ellipse",image); waitKey();



    return 0;
}
