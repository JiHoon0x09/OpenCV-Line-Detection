#include "OpenCV_Functions.h"

using namespace std;
using namespace cv;
void imageProcessing(Mat &image, Mat &result){
    Mat white, yellow, hls;
    result = imageCopy(image);
    //cvtColor(image, result, COLOR_BGR2HLS);
    Scalar white_lower(0, 200, 0);
    Scalar white_upper(179,255,255);
    Scalar yellow_lower(15,30,115);
    Scalar yellow_upper(35,204,255);

    
    convertColor(result, hls, COLOR_BGR2HLS);
    splitColor(hls, yellow, yellow_lower,yellow_upper);
    splitColor(hls, white, white_lower, white_upper);
    hls = yellow + white;
    convertColor(hls, result, COLOR_HLS2BGR);
    

    /*
    rangeColor(result, white, white_lower, white_upper);
    rangeColor(result, yellow, yellow_lower, yellow_upper);
    result = white + yellow;
    */

    return;
}

int main(void){
    vector<string> images;
    images = imageList_LaneDetection();
    int idx=0;
    for (string path : images){
        Mat image = imageRead(path);
        imageShow("Image index is " + to_string(idx), image);
        Mat result;
        imageProcessing(image, result);
        imageShow("Result of index " + to_string(idx), result);
        imageWrite("Result_" + to_string(idx) + ".jpg", result);
        idx++;
    }

    return 0;
}
