void imageProcessing(Mat &image, Mat &result)
{
    result = imageCopy(image);
    convertColor(result, result, COLOR_BGRA2BGR);
    vector<Point> src_pts, dst_pts;
    int x1, y1, x2, y2;
    x1 = 888;
    y1 = 445;
    x2 = 908;
    y2 = 455;
    int h = result.rows;
    int w = result.cols;
    src_pts.push_back(Point(x1, y1));
    src_pts.push_back(Point(x2, y1));
    src_pts.push_back(Point(x2, y2));
    src_pts.push_back(Point(x1, y2));
    dst_pts.push_back(Point(int(w * 0.4), int(h * 0.4)));
    dst_pts.push_back(Point(int(w * 0.6), int(h * 0.4)));
    dst_pts.push_back(Point(int(w * 0.6), int(h * 0.6)));
    dst_pts.push_back(Point(int(w * 0.4), int(h * 0.6)));
    imagePerspectiveTransformation(result, result, src_pts, dst_pts, Size(w, h));
    
   return;
}