OpenCV_Utils.h
void overlayToImage(Mat &backGroungImage, Mat &overlayImage, Mat &dstImage, double fx = 0.2, double fy = 0.2);

OpenCV_Utils.cpp
void overlayToImage(Mat &backGroungImage, Mat &overlayImage, Mat &dstImage, double fx, double fy)
{
    Mat temp1, temp2;
    imageResize(overlayImage, temp1, Size(), fx, fy);
    int w2 = temp1.cols;
    temp2 = imageCopy(backGroungImage);
    PasteRectROI(temp1, temp2, Point(temp2.cols-w2, 0));
    dstImage = imageCopy(temp2);
    return;
}