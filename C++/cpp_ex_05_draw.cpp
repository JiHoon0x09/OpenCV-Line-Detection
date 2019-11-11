void imageProcessing(Mat &image, Mat &result)
{
    result = imageCopy(image);
    Point pt1(430, 310);
    Point pt2(530, 310);
    Point pt3(940, 540);
    Point pt4(20, 540);
    drawLine(result, result, pt1, pt2, Scalar(255, 0, 0), 5);
    drawLine(result, result, pt2, pt3, Scalar(255, 0, 0), 5);
    drawLine(result, result, pt3, pt4, Scalar(255, 0, 0), 5);
    drawLine(result, result, pt4, pt1, Scalar(255, 0, 0), 5);
    int width = result.cols;
    int height = result.rows;
    pt1 = Point(width*0.5, height*0.5);
    pt2 = Point(width, height);
    pt3 = Point(0, height);
    drawLine(result, result, pt1, pt2, Scalar(0, 255, 0), 5);
    drawLine(result, result, pt2, pt3, Scalar(0, 255, 0), 5);
    drawLine(result, result, pt3, pt1, Scalar(0, 255, 0), 5);
    Rect rect(Point(0,0), pt2);
    drawRect(result, result, rect, Scalar(0, 0, 0), 5);
    drawCircle(result, result, pt1, 30, Scalar(255, 255, 255), -1);
    return;
}