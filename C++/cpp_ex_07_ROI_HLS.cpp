void imageProcessing(Mat &image, Mat &result)
{
    result = imageCopy(image);
    Mat roi_active, roi_deactive;
    int width = result.cols;
    int height = result.rows;
    vector<Point> points;
    points.push_back(Point(width*0.35, height*0.65));
    points.push_back(Point(width*0.65, height*0.65));
    points.push_back(Point(width*1.0, height*1.0));
    points.push_back(Point(width*0.0, height*1.0));
    polyROI(result, roi_active, points);
    roi_deactive = result - roi_active;
    Mat hls, white_image, yellow_image;
    Scalar yellow_lower(15, 140, 70);
    Scalar yellow_upper(45, 255, 255);
    Scalar white_lower(0, 150, 0);
    Scalar white_upper(180, 255, 255);
    convertColor(roi_active, hls, COLOR_BGR2HLS);
    rangeColor(hls, yellow_image, yellow_lower, yellow_upper);
    rangeColor(hls, white_image, white_lower, white_upper);
    hls = yellow_image + white_image;
    convertColor(hls, hls, COLOR_GRAY2BGR);
    bitwise_and(hls, roi_active, roi_active);
    addWeightedImage(roi_active, roi_deactive, result, 100, 100);
    return;
}