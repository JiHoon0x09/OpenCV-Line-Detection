#include "OpenCV_Functions.h"

using namespace std;
using namespace cv;

int main(void){
    int i, j;
    string name = path_to_images();
    Mat image = imread(name);
    namedWindow("image 1",WINDOW_GUI_EXPANDED);
    imshow("image 1",image);
    waitKey();

    convertColor(image,image,COLOR_BGR2HLS);
    namedWindow("HLS",WINDOW_GUI_EXPANDED);    imshow("HLS",image);    waitKey();
    vector<Mat> Ch;
    split(image, Ch);
    Mat h, l, s;
    h = Ch[0]; l = Ch[1]; s = Ch[2];
    namedWindow("H",WINDOW_GUI_EXPANDED);    imshow("H",h);    waitKey();
    namedWindow("L",WINDOW_GUI_EXPANDED);    imshow("L",l);    waitKey();
    namedWindow("S",WINDOW_GUI_EXPANDED);    imshow("S",s);    waitKey();
    
    for(i=0; i<200; i++){
        for(j=0; j<200; j++){
            setPixel(l, i, j, 200, 0);
        }
    }
    namedWindow("after L",WINDOW_GUI_EXPANDED);    imshow("after L",l);    waitKey();

    mergeImage(h, l, s, image);
    namedWindow("MergeHLS",WINDOW_GUI_EXPANDED);    imshow("MergeHLS",image);    waitKey();

    cvtColor(image,image,COLOR_HLS2BGR);
    namedWindow("MergeBGR",WINDOW_GUI_EXPANDED);    imshow("MergeBGR",image);    waitKey();

    return 0;

}
