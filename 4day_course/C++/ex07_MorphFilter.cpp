#include "OpenCV_Functions.h"
#include "OpenCV_Utils.h"
using namespace std;
using namespace cv;


void imageProcessing2(Mat &image, Mat &result)
{
    result = imageCopy(image);
    Mat cross;
    imageMorphologyKernel(cross, MORPH_CROSS, 3);
    imageMorphologyEx(result, result, MORPH_GRADIENT, cross);
    cvtColor(result, result, COLOR_BGR2GRAY);
    imageThreshold(result, result, 50, 255, THRESH_BINARY);
    return;
}

void Video2(string openPath, string savePath){
    VideoCapture cap(openPath);
    if(cap.isOpened())
        cout << "Video Opened" << endl;
    else{
        cout << "Video Not Opened" << endl;
        cout << "Program Abort" << endl;
        exit(-1);
    }

    int fps = cap.get(CAP_PROP_FPS);
    int width = cap.get(CAP_PROP_FRAME_WIDTH);
    int height = cap.get(CAP_PROP_FRAME_HEIGHT);
    int fourcc = cap.get(CAP_PROP_FOURCC);
    VideoWriter out(savePath.c_str(), fourcc, fps, Size(width, height), true);
    namedWindow("Input", WINDOW_GUI_EXPANDED);
    namedWindow("Output", WINDOW_GUI_EXPANDED);
    Mat frame, output;
    while(cap.read(frame)){
         imageProcessing2(frame, output);
         out.write(output);
         imshow("Input", frame);
         imshow("Output", output);
         char c = (char)waitKey(int(1000.0/fps));
         if (c==27)
             break;
    }
    cap.release();
    out.release();
    destroyAllWindows();
    return ;
}

void processingSingleVideo2(string videoPath, string outputPath){
    Video2(videoPath, outputPath);
    return;
}        
int main(void){
    processingSingleVideo2(path_to_videos(), "output.mp4");
    return 0;
}
