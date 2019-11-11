#include "OpenCV_Functions.h"

using namespace std;

int main(void) 
{
    string imagepath = path_to_images();
    Mat image = imageRead(imagepath);
    imageShow("image", image);
    vector<int> params = imageParameters("image", image);
    int x_start = 99;
    int x_end = 101;
    for( int i = x_start; i < x_end+1 ; i++) {
        for (int j = 0 ; j < params[0] ; j++) {
            setPixel(image, i, j, 255, 0);
            setPixel(image, i, j, 0, 1);
            setPixel(image, i, j, 0, 2);
        }
    }
    imageShow("image", image);
    return 0;
}