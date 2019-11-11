void polyROI(Mat &image, Mat &result, vector<Point> points) 
{
    Mat result_ = fillPolyROI(image, points);
    bitwise_and(result_, image, result);
    return;
}