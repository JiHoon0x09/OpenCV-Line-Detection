OpenCV_Utils.h
void splitTwoSideLinesForPerspectiveImage(vector<Vec4i> &lines, vector<vector<float>> &lefts, vector<vector<float>> &rights, int middle_x, float slope_threshold = (30.0 * PI / 180.0));
void lineFittingForPerspectiveImage(Mat &image, Mat &result, vector<Vec4i> &lines, Scalar color = Scalar(0, 0, 255), int thickness = 3, float slope_threshold = (30.0 * PI / 180.0));

OpenCV_Utils.cpp
void splitTwoSideLinesForPerspectiveImage(vector<Vec4i> &lines, vector<vector<float> > &lefts, vector<vector<float> > &rights, int middle_x, float slope_threshold)
{
    int i;
    lefts.clear();
    rights.clear();
    vector<float> temp;
    for( i = 0 ; i < lines.size() ; i++ )
    {
        temp.clear();
        Vec4i line = lines[i];
        int x1, y1, x2, y2;
        x1 = line[0];
        y1 = line[1];
        x2 = line[2];
        y2 = line[3];
        if(x1 < middle_x && x2 < middle_x) // left
        {
            float slope;
            if(x1 - x2 <= 0.001)
                slope = 999.;
            else
                slope = (float)(y2-y1)/(float)(x2-x1);
            if (abs(slope) < slope_threshold || y1 == y2)
                continue;
            temp.push_back(slope);
            temp.push_back(x1);
            temp.push_back(y1);
            temp.push_back(x2);
            temp.push_back(y2);
            lefts.push_back(temp);
        }
        else if (x1 > middle_x && x2 > middle_x) // right
        {
            float slope;
            if(x1 - x2 <= 0.001)
                slope = 999.;
            else
                slope = (float)(y2-y1)/(float)(x2-x1);
            if (abs(slope) < slope_threshold || y1 == y2)
                continue;
            temp.push_back(slope);
            temp.push_back(x1);
            temp.push_back(y1);
            temp.push_back(x2);
            temp.push_back(y2);
            rights.push_back(temp);
        }
    }
    return;
}
void lineFittingForPerspectiveImage(Mat &image, Mat &result, vector<Vec4i> &lines, Scalar color, int thickness, float slope_threshold)
{
    result = imageCopy(image);
    int height = image.rows;
    int middle_x = int(0.5 * image.cols);
    vector<vector<float> > lefts, rights;
    splitTwoSideLinesForPerspectiveImage(lines, lefts, rights, middle_x, slope_threshold);
    vector<float> left, right;
    medianPoint(lefts, left);
    medianPoint(rights, right);
    int min_y = 0.0;
    int max_y = height;
    int min_x_left, max_x_left, min_x_right, max_x_right;
    if( !left.empty()) 
    {
        min_x_left = interpolate(left[1], left[2], left[3], left[4], min_y);
        max_x_left = interpolate(left[1], left[2], left[3], left[4], max_y);
        line(result, Point(min_x_left, min_y), Point(max_x_left, max_y), color, thickness);
    }
    if( !right.empty())
    {
        min_x_right = interpolate(right[1], right[2], right[3], right[4], min_y);
        max_x_right = interpolate(right[1], right[2], right[3], right[4], max_y);
        line(result, Point(min_x_right, min_y), Point(max_x_right, max_y), color, thickness);
    }
    if (!left.empty() && !right.empty())
    {   
        vector<Point> pts;
        pts.push_back(Point(min_x_left, min_y));
        pts.push_back(Point(min_x_right, min_y));
        pts.push_back(Point(max_x_right, max_y));
        pts.push_back(Point(max_x_left, max_y));
        vector<vector<Point> > fillContAll;
        fillContAll.push_back(pts);
        fillPoly(result, fillContAll, Scalar(0, 255, 0));
    }
    return;
}