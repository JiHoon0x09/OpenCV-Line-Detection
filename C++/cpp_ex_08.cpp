void imageProcessing(Mat &image, Mat &result)
{
    result = imageCopy(image);
    int width = result.cols;
    int height = result.rows;
    Mat roi_active, roi_deactive;
    vector<Point> points;
    points.push_back(Point(width*0.35, height*0.65));
    points.push_back(Point(width*0.65, height*0.65));
    points.push_back(Point(width, height));
    points.push_back(Point(0, height));
    polyROI(result, roi_active, points);
    roi_deactive = result-roi_active;
    Mat roi_re_ac, roi_re_de;
    imageBilateralFilter(roi_active, roi_active, 10, 10, 10);
    imageMedianBlur(roi_deactive, roi_deactive, 5);
    addWeightedImage(roi_active, roi_deactive, result, 100, 100);
    return;
}

void imageBilateralFilter(Mat &image, Mat &result, int ksize, double sigmaColor, double sigmaSpace)
{
	Mat result_ = imageCopy(image);
	bilateralFilter(image, result_, ksize*2-1, sigmaColor, sigmaSpace);
	result = imageCopy(result_);
	return;
}