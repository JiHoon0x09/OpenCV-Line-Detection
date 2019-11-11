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
    imageHoughLinesP(result, lines, 1.0, 1.0 * PI / 180.0 ,  100, 50, 50);
    Mat blackLineImage;
    blackLineImage = makeBlackImage(result, true);
    lineFittingForPerspectiveImage(blackLineImage, blackLineImage, lines, Scalar(0, 0, 255), 10, 60.0*PI/180.0);
    imagePerspectiveTransformation(blackLineImage, result, dst_pts, src_pts, Size());
    result = result + image;
    overlayToImage(result, blackLineImage, result, 0.2, 0.2);
    return;
}