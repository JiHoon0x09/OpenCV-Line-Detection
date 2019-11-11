#include "OpenCV_Functions.h"
#include "OpenCV_Utils.h"
using namespace std;
using namespace cv;

void processingSingleImage2(string imagePath, string outputPath = "output.jpg");
void processingSingleVideo2(string videoPath, string outputPath = "output.mp4");
void RectROI(Mat &image, Mat &result){
    result = imageCopy(image);
    convertColor(result, result, COLOR_BGR2GRAY);
    imageMorphologicalGradient(result, result);
    cannyEdge(result, result, 100, 200);
     
    int width = result.cols;
    int height = result.rows;
    vector<Point> src_pts, dst_pts;
    vector<Vec4i> lines;
    src_pts.push_back(Point(int(width*0.4), int(height*0.65)));
    src_pts.push_back(Point(int(width*0.6), int(height*0.65)));
    src_pts.push_back(Point(int(width*0.9), int(height*0.9)));
    src_pts.push_back(Point(int(width*0.1), int(height*0.9)));
    dst_pts.push_back(Point(int(width*0.1), int(height*0.0)));
    dst_pts.push_back(Point(int(width*0.9), int(height*0.0)));
    dst_pts.push_back(Point(int(width*0.9), int(height*1.0)));
    dst_pts.push_back(Point(int(width*0.1), int(height*1.0)));
    imagePerspectiveTransformation(result, result, src_pts, dst_pts, Size());
    imageHoughLinesP(result, lines, 1.0, 1.0 * PI / 180.0 ,  50, 10, 10);
    Mat blackLineImage;
    blackLineImage = makeBlackImage(result, true);
    drawHoughLinesP(blackLineImage, lines, Scalar(0, 0, 255), 5);
    imagePerspectiveTransformation(blackLineImage, result, dst_pts, src_pts, Size());
    result = result + image;
     
    imageResize(blackLineImage, blackLineImage, Size(), 0.2, 0.2);
    int w2 = blackLineImage.cols;
   
    Mat result2 = imageCopy(result);
    PasteRectROI(blackLineImage, result2, Point(int(result2.cols-w2), 0));
    result = imageCopy(result2);
    
    return ;
}
void imageProcessing2(Mat &image, Mat &result){
    Mat input, edge;
    Mat active, deactive;
    vector<Point> sp, dp;

    input = imageCopy(image);
    int w = input.cols, h = input.rows;

    sp.push_back(Point(int(w*0.4), int(h*0.65)));
    sp.push_back(Point(int(w*0.6), int(h*0.65)));
    sp.push_back(Point(int(w*1.0), int(h*1.0)));
    sp.push_back(Point(int(w*0.0), int(h*1.0)));
    dp.push_back(Point(int(w*0.1), 0));
    dp.push_back(Point(int(w*0.9), 0));
    dp.push_back(Point(int(w*0.9), h));
    dp.push_back(Point(int(w*0.1), h));
    
    Scalar whiteLower(0, 200, 0);
    Scalar whiteUpper(180, 255, 255);
    Scalar yellowLower(15, 30, 115);
    Scalar yellowUpper(35, 204, 255);

    Mat HLS, white, yellow, sImage;
    cvtColor(input, HLS, COLOR_BGR2HLS);
    splitColor(HLS, white, whiteLower, whiteUpper);
    splitColor(HLS, yellow, yellowLower, yellowUpper);
    HLS = white + yellow;
    cvtColor(HLS, sImage, COLOR_HLS2BGR);
    namedWindow("sImage",WINDOW_GUI_EXPANDED);
    imshow("sImage",sImage);
     
    cannyEdge(sImage, edge, 100, 200);
    polyROI(edge, active, sp);
    deactive = edge - active;
//    namedWindow("active",WINDOW_GUI_EXPANDED);
//    imshow("active",active);
     
    vector<Vec4i> lines;
    Mat black;
    black = makeBlackImage(active, true);
    imageHoughLinesP(active, lines, 1.0, 1.0*PI/180.0, 50, 10, 10);
    drawHoughLinesP(black, lines, Scalar(0,0,255), 7);
//    namedWindow("black",WINDOW_GUI_EXPANDED);
//    imshow("black",black);

    //imagePerspectiveTransformation(black, output, dp, sp, Size());
    lineFitting(image, result, lines, Scalar(0,0,255), 5, 10*PI/180.0);
    namedWindow("result",WINDOW_GUI_EXPANDED);
    imshow("result",result);

//    RectROI(result, HLS);
  //  result = imageCopy(HLS);
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
