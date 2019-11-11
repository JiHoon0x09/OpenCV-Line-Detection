#include "OpenCV_Functions.h"

using namespace std;
using namespace cv;

int main(void){
    int i, j;
    string name = path_to_images();
    Mat image = imread(name);
    namedWindow("image",WINDOW_GUI_EXPANDED); imshow("image",image); waitKey();
    Mat Line, Tri, Rec, Cir;
    vector<int> result = imageParameters(name, image);
    int w = result[0];
    int h = result[1];
    printf(" w = %d, h = %d\n",w, h);
    Scalar blue(255,0,0);
    Point pl1(430,310);
    Point pl2(530,310); 
    Point pl3(940,530); 
    Point pl4(20,540);

    Line = image;
    drawLine(Line,Line,pl1,pl2,blue,5);
    drawLine(Line,Line,pl2,pl3,blue,5);
    drawLine(Line,Line,pl3,pl4,blue,5);
    drawLine(Line,Line,pl1,pl4,blue,5);
    namedWindow("Line",WINDOW_GUI_EXPANDED); imshow("Line",Line); waitKey();

    Scalar Green(0,255,0);
    Point pt1(480, 270);
    Point pt2(960, 540);
    Point pt3(0, 540);
    Tri = image;
    drawLine(Tri,Tri,pt1,pt2,Green,5);
    drawLine(Tri,Tri,pt2,pt3,Green,5);
    drawLine(Tri,Tri,pt1,pt3,Green,5);
    namedWindow("Tri",WINDOW_GUI_EXPANDED); imshow("Tri",Tri); waitKey();

 
    Point pr1(0, 0);
    Point pr2(960, 540);
    Rec = image;
    drawRect(Rec, Rec, pr1, pr2, Scalar(0,0,0),7);
    namedWindow("Rec",WINDOW_GUI_EXPANDED); imshow("Rec",Rec); waitKey();

    Point pc(int(h*0.5),int(w*0.5));
    Cir = image;
    drawCircle(Cir,Cir,pc,30,Scalar(255,255,255),-1);
    namedWindow("Cir",WINDOW_GUI_EXPANDED); imshow("Cir",Cir); waitKey();




    return 0;
}
