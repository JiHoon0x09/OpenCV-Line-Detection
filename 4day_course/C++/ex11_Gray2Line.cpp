#include "OpenCV_Functions.h"
#include "OpenCV_Utils.h"
using namespace std;
using namespace cv;

void processingSingleImage2(string imagePath, string outputPath = "output.jpg");
void processingSingleVideo2(string videoPath, string outputPath = "output.mp4");

void imageProcessing2(Mat &image, Mat &result){
    Mat input, edge;
    Mat active, deactive;
    vector<Point> sp, dp;

    convertColor(image, input, COLOR_BGR2GRAY);
    int w = input.cols, h = input.rows;
    sp.push_back(Point(int(w*0.4), int(h*0.65)));
    sp.push_back(Point(int(w*0.6), int(h*0.65)));
    sp.push_back(Point(int(w*1.0), int(h*1.0)));
    sp.push_back(Point(int(w*0.0), int(h*1.0)));
    dp.push_back(Point(int(w*0.1), 0));
    dp.push_back(Point(int(w*0.9), 0));
    dp.push_back(Point(int(w*0.9), h));
    dp.push_back(Point(int(w*0.1), h));
   

    cannyEdge(input, edge, 100, 200);
    namedWindow("edge",WINDOW_GUI_EXPANDED);
    imshow("edge",edge);

    polyROI(edge, active, sp);
    deactive = edge - active;
    namedWindow("active",WINDOW_GUI_EXPANDED);
    imshow("active",active);
    Mat range;   
    Scalar white_lower(150, 150, 150);
    Scalar white_upper(255, 255, 255);
    rangeColor(active, range, white_lower, white_upper);
    
    //imageMorphologicalGradient(active, active);
    //imagePerspectiveTransformation(edge, p_image, sp, dp, Size());
    //namedWindow("p_image",WINDOW_GUI_EXPANDED);
    //imshow("p_image",p_image);
     
    vector<Vec4i> lines;
    Mat black, output;
    black = makeBlackImage(range, true);
    imageHoughLinesP(range, lines, 1.0, 1.0*PI/180.0, 50, 10, 10);
    drawHoughLinesP(black, lines, Scalar(0,0,255), 7);
    namedWindow("black",WINDOW_GUI_EXPANDED);
    imshow("black",black);

    //imagePerspectiveTransformation(black, output, dp, sp, Size());
    lineFitting(image, result, lines, Scalar(0,0,255), 5, 10*PI/180.0);
    namedWindow("result",WINDOW_GUI_EXPANDED);
   imshow("result",result);
    return ;
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
    processingSingleVideo2(path_to_videos(), "output.mp4");
    //processingSingleImage2("../../Data/Lane_Detection_Images/test.png");
    return 0;
}
