void lineFitting(Mat &image, Mat &result, vector<Vec4i> &lines, Scalar color, int thickness, float slope_threshold)
{
    result = imageCopy(image);
    int height = image.rows;
    vector<vector<float>> lefts, rights;
    splitTwoSideLines(lines, lefts, rights, slope_threshold);
    vector<float> left, right;
    medianPoint(lefts, left);
    medianPoint(rights, right);
    int min_y = int(height * 0.6);
    int max_y = height;
    if( !left.empty()) 
    {
        int min_x_left = interpolate(left[1], left[2], left[3], left[4], min_y);
        int max_x_left = interpolate(left[1], left[2], left[3], left[4], max_y);
        line(result, Point(min_x_left, min_y), Point(max_x_left, max_y), color, thickness);
    }
    if( !right.empty())
    {
        int min_x_right = interpolate(right[1], right[2], right[3], right[4], min_y);
        int max_x_right = interpolate(right[1], right[2], right[3], right[4], max_y);
        line(result, Point(min_x_right, min_y), Point(max_x_right, max_y), color, thickness);
    }
    return;
}