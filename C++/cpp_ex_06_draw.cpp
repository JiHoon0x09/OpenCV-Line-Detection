void imageProcessing(Mat &image, Mat &result)
{
    result = imageCopy(image);
    int width = result.cols;
    int height = result.rows;
    Point pt1(width*0.35, height*0.65);
    Point pt2(width*0.65, height*0.65);
    Point pt3(width*1.0, height*1.0);
    Point pt4(width*0.0, height*1.0);
    vector<Point> points;
    points.push_back(pt1);
    points.push_back(pt2);
    points.push_back(pt3);
    points.push_back(pt4);
    drawPolygon(result, result, points, true, Scalar(255, 0, 0), 5);
    drawText(result, result, "OpenCV Image Processing", Point(10, 50), 1, 2.0, Scalar(0, 255, 0), 3);
    drawEllipse(result, result, Point(width*0.5, height*0.5), Size(30, 30), 0, 0, 360, Scalar(255, 255, 255), -1);
    return;
}