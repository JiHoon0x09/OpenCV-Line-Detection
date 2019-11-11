void imageProcessing(Mat &image, Mat &result)
{
    result = imageCopy(image);
    convertColor(result, result, COLOR_BGR2GRAY);
    imageMorphologicalGradient(result, result);
    cannyEdge(result, result, 100, 200);
    int width = result.cols;
    int height = result.rows;
    vector<Point> points;
    vector<Vec4i> lines;
    points.push_back(Point(width*0.4, height*0.65));
    points.push_back(Point(width*0.6, height*0.65));
    points.push_back(Point(width*0.9, height*0.9));
    points.push_back(Point(width*0.1, height*0.9));
    polyROI(result, result, points);
    /*
    void polyROI(Mat &image, Mat &result, vector<Point> points) 
    {
        Mat result_ = fillPolyROI(image, points);
        bitwise_and(result_, image, result);
        return;
    } */
    imageHoughLinesP(result, lines, 1.0, 1.0 * PI / 180.0 ,  50, 10, 10);
    result = imageCopy(image);
    drawHoughLinesP(result, lines, Scalar(255, 0, 0), 5);
    return;
}