#include "OpenCV_Functions.h"

using namespace std;
using namespace cv;

int main(void){
    int i, j;
    string name = path_to_images();
    Mat image = imread(name);
    vector<int> Result = imageParameters(name, image);

    namedWindow("image 1",WINDOW_GUI_EXPANDED);
    imshow("image 1",image);
    waitKey();
    
    int width = Result[0];
    int height = Result[1];
    printf("Width = %d, height = %d\n",width, height);

    printf("B G R Color : ");
    for(i=0; i<3; i++){
        printf("(%d = %d) ",i,getPixel(image,100,100,i));
    }
    printf("\n");

    for(i=99; i<=101; i++){
            for(int j=0; j<540; j++){
                setPixel(image, i, j, 255, 0);
                setPixel(image, i, j, 0, 1);
                setPixel(image, i, j, 0, 2);
            }
    }
   

    namedWindow("image 2",WINDOW_GUI_EXPANDED);
    imshow("image 2",image);
    waitKey();
    return 0;

}
