void imageProcessing(Mat &image, Mat &result)
{
    result = imageCopy(image);
    Mat roi_active, roi_deactive, hsv, hls, rgb, white_image, yellow_image;
    vector<Mat> channels;
    int width = result.cols;
    int height = result.rows;
    vector<Point> points;
    points.push_back(Point(width*0.35, height*0.65));
    points.push_back(Point(width*0.65, height*0.65));
    points.push_back(Point(width*1.0, height*1.0));
    points.push_back(Point(width*0.0, height*1.0));
    polyROI(result, roi_active, points);
    roi_deactive = result - roi_active;
    convertColor(roi_active, hsv, COLOR_BGR2HSV);
    splitImage(hsv, channels);
    histogramEqualize(channels[1], channels[1]);
    histogramEqualize(channels[2], channels[2]);
    mergeImage(channels, hsv);
    convertColor(hsv, rgb, COLOR_HSV2RGB);
    convertColor(rgb, roi_active, COLOR_RGB2HLS);
    Scalar yellow_lower(10, 100, 100);
    Scalar yellow_upper(25, 180, 255);
    Scalar white_lower(0, 240, 0);
    Scalar white_upper(180, 255, 255);
    rangeColor(roi_active, yellow_image, yellow_lower, yellow_upper);
    rangeColor(roi_active, white_image, white_lower, white_upper);
    roi_active = yellow_image + white_image;
    convertColor(roi_active, roi_active, COLOR_GRAY2BGR);
    addWeightedImage(roi_active, roi_deactive, result, 100, 100);
    return;
}