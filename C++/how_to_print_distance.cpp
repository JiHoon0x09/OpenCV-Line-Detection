void imageProcessing(Mat &image, Mat &result)
{
    result = imageCopy(image);
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
    Scalar yellow_lower(15, 140, 70);
    Scalar yellow_upper(45, 255, 255);
    Scalar white_lower(0, 150, 0);
    Scalar white_upper(180, 255, 255);
    Mat yellow_image, white_image;
    rangeColor(result, yellow_image, yellow_lower, yellow_upper, COLOR_BGR2HLS);
    rangeColor(result, white_image, white_lower, white_upper, COLOR_BGR2HLS);
    result = yellow_image + white_image;
    imageMorphologicalGradient(result, result);
    cannyEdge(result, result, 100, 200);
    imageHoughLinesP(result, lines, 1.0, 1.0 * PI / 180.0 , 50, 10, 20);
    Mat blackLineImage;
    //convertColor(result, blackLineImage, COLOR_GRAY2BGR);
    blackLineImage = makeBlackImage(result, true);
    int distance;
    distance = lineFittingForPerspectiveImage(blackLineImage, blackLineImage, lines, Scalar(0, 0, 255), 10, 60.0*PI/180.0);
    cout << distance << endl;
    imagePerspectiveTransformation(blackLineImage, result, dst_pts, src_pts, Size());
    result = result + image;
    overlayToImage(result, blackLineImage, result, 0.2, 0.2);
    return;
}