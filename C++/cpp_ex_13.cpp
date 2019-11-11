void imageProcessing(Mat &image, Mat &result)
{
    result = imageCopy(image);
    convertColor(result, result, COLOR_BGR2GRAY);
    imageMorphologicalGradient(result, result);
    cannyEdge(result, result, 100, 200);
    int width = result.cols;
    int height = result.rows;
    vector<Point> src_pts, dst_pts;
    vector<Vec4i> lines;
    src_pts.push_back(Point(width*0.40, height*0.65));
    src_pts.push_back(Point(width*0.6, height*0.65));
    src_pts.push_back(Point(width*0.9, height*0.9));
    src_pts.push_back(Point(width*0.1, height*0.9));
    dst_pts.push_back(Point(width*0.1, height*0.0));
    dst_pts.push_back(Point(width*0.9, height*0.0));
    dst_pts.push_back(Point(width*0.9, height*1.0));
    dst_pts.push_back(Point(width*0.1, height*1.0));
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
    PasteRectROI(blackLineImage, result2, Point(result2.cols-w2, 0));
    /*
    void PasteRectROI(Mat &image, Mat &result, Point pt1)
    {   
        int y2 = image.rows + pt1.y;
        int x2 = image.cols + pt1.x;
        Mat dstROI(result, Rect(pt1, Point(x2, y2)));
        image.copyTo(dstROI);
        return;
    }*/
    result = imageCopy(result2);
    return;
}