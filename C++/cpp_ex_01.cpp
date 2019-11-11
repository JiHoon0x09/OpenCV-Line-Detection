#include "OpenCV_Functions.h"

using namespace std;

int main(void) 
{
    cv::Mat image = cv::imread("../../Data/Lenna.png");
    cv::namedWindow("image", cv::WINDOW_GUI_EXPANDED);
    cv::imshow("image", image);
    cv::waitKey();
    return 0;
}