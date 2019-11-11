#include "OpenCV_Functions.h"
#include "OpenCV_Utils.h"
using namespace std;
using namespace cv;

void processingSingleImage2(string imagePath, string outputPath = "output.jpg");
void processingSingleVideo2(string videoPath, string outputPath = "output.mp4");

void imageProcessing2(Mat &image, Mat &result){
    Mat bgr;
    result = imageCopy(image);
    cvtColor(result, bgr, COLOR_BGRA2BGR);
    namedWindow("position",WINDOW_GUI_EXPANDED);
    imshow("position",bgr);waitKey();

    int w = result.cols, h = result.rows;
    vector<Point> sptr, dptr;
    sptr.push_back(Point(888, 445));
    sptr.push_back(Point(908, 445));
    sptr.push_back(Point(908, 455));
    sptr.push_back(Point(888, 455));

    dptr.push_back(Point(int(w*0.45), int(h*0.45)));
    dptr.push_back(Point(int(w*0.55), int(h*0.45)));
    dptr.push_back(Point(int(w*0.55), int(h*0.55)));
    dptr.push_back(Point(int(w*0.45), int(h*0.55)));

    imagePerspectiveTransformation(result, result, sptr, dptr, Size());
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
void processingSingleImage2(string imagePath, string outputPath)
{
    Mat image = imageRead(imagePath);
    imageShow("Opened Image", image);
    Mat result;
    imageProcessing2(image, result);
    cout << "test" << endl;
    imageShow("Result Image", result);
    imageWrite(outputPath, result);
    return;
}
void processingSingleVideo2(string videoPath, string outputPath){
    Video2(videoPath, outputPath);
    return;
}        
int main(void){
    //processingSingleVideo2(path_to_videos(), "output.mp4");
    processingSingleImage2("../../Data/Lane_Detection_Images/test.png");
    return 0;
}
