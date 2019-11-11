#include "OpenCV_Functions.h"
#include "OpenCV_Utils.h"
using namespace std;
using namespace cv;

void processingSingleImage2(string imagePath, string outputPath = "output.jpg");
void processingSingleVideo2(string videoPath, string outputPath = "output.mp4");
void RectROI(Mat &image, Mat &result){
    return ;
}
void imageProcessing2(Mat &image, Mat &result){
    Mat inIm, filterIm, edgeIm;
    inIm = imageCopy(image);
    cvtColor(inIm, inIm, COLOR_BGR2GRAY);
    imageMorphologicalGradient(inIm, filterIm);
    Canny(filterIm, edgeIm, 100, 200);
    namedWindow("edge Image",WINDOW_GUI_EXPANDED);
    imshow("edge Image", edgeIm);
    //edgeIm
    
    Mat RoiIm;
    vector<Point> pt;
    int w = edgeIm.cols, h = edgeIm.rows;
    pt.push_back(Point(int(w*0.45), int(h*0.46)));
    pt.push_back(Point(int(w*0.55), int(h*0.46)));
    pt.push_back(Point(int(w*1.0), int(h*0.7)));
    pt.push_back(Point(int(w*0.0), int(h*0.7)));
    polyROI(edgeIm, RoiIm, pt);
    namedWindow("Roi Image",WINDOW_GUI_EXPANDED);
    imshow("Roi Image",RoiIm);
    //RoiIm

    Mat LineIm, blackIm = makeBlackImage(RoiIm,true);
    Mat areaIm = imageCopy(blackIm);

    vector<Vec4i> lines;
    imageHoughLinesP(RoiIm, lines, 1.0, 1.0*PI/180., 50, 10, 10);
    lineFitting(image, LineIm, lines, Scalar(0,0,255), 3, 10*PI/180.);
    lineFittingForPerspectiveImage(areaIm, areaIm, lines, Scalar(0,0,255), 7, 10*PI/180.);
    namedWindow("area Image",WINDOW_GUI_EXPANDED);
    imshow("area Image",areaIm);
    namedWindow("Line Image",WINDOW_GUI_EXPANDED);
    imshow("Line Image",LineIm);
    //LineIm

    Mat wIm;
    addWeightedImage(LineIm, areaIm, wIm, 100, 30);
    namedWindow("weighted Image",WINDOW_GUI_EXPANDED);
    imshow("weighted Image",wIm);
    //wIm
   
    Mat upperIm; 
    vector<Point> Spt, Dpt;
    Spt.push_back(Point(int(w*0.35), int(h*0.5)));
    Spt.push_back(Point(int(w*0.65), int(h*0.5)));
    Spt.push_back(Point(int(w*1.0), int(h*0.7)));
    Spt.push_back(Point(int(w*0.0), int(h*0.7)));

    Dpt.push_back(Point(int(w*0.0), int(h*0.0)));
    Dpt.push_back(Point(int(w*1.0), int(h*0.0)));
    Dpt.push_back(Point(int(w*1.0), int(h*1.0)));
    Dpt.push_back(Point(int(w*0.0), int(h*1.0)));
    imagePerspectiveTransformation(wIm, upperIm, Spt, Dpt, Size());
    namedWindow("upper Image",WINDOW_GUI_EXPANDED);
    imshow("upper Image",upperIm);
    // upperIm
     
    Mat overIm;
    overlayToImage(wIm, upperIm, overIm, 0.2, 0.2);
    namedWindow("over Image",WINDOW_GUI_EXPANDED);
    imshow("over Image",overIm);

    result = imageCopy(overIm);

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
    processingSingleVideo2("/home/opencv-mds/OpenCV_in_Ubuntu/Data/Lane_Detection_Projects/PC_T_01.mp4", "output.mp4");

    //processingSingleImage2("../../Data/Lane_Detection_Images/test.png");
    return 0;
}
