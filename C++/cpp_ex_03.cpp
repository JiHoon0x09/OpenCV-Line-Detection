#include "OpenCV_Functions.h"

using namespace std;

int main(void) 
{
    string imagepath = path_to_images();
    Mat image = imageRead(imagepath);
    imageShow("image", image);
    vector<int> params = imageParameters("image", image);
    int x_start = 0;
    int x_end = 200;
    int y_start = 0;
    int y_end = 200;
    Mat hls, l, result;
    vector<Mat> channels;
    convertColor(image, hls, COLOR_BGR2HLS);
    //splitImage(hls, channels);
    //l = channels[1];
    for( int i = x_start; i < x_end+1 ; i++) {
        for (int j = y_start ; j < y_end+1 ; j++) {
            //setPixel(l, i, j, 200, 0);
            setPixel(hls, i, j, 200, 1);
        }
    }
    //mergeImage(channels[0], l, channels[2], result);
    convertColor(hls, result, COLOR_HLS2BGR);
    imageShow("result", result);
    return 0;
}