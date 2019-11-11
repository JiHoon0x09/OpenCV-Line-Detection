void imageProcessing(Mat &image, Mat &result)
{
    result = imageCopy(image);
    Mat hls, white_image, yellow_image;
    Scalar yellow_lower(15, 140, 70);
    Scalar yellow_upper(45, 255, 255);
    Scalar white_lower(0, 150, 0);
    Scalar white_upper(180, 255, 255);
    convertColor(result, hls, COLOR_BGR2HLS);
    rangeColor(hls, yellow_image, yellow_lower, yellow_upper);
    rangeColor(hls, white_image, white_lower, white_upper);
    hls = yellow_image + white_image;
    convertColor(hls, hls, COLOR_GRAY2BGR);
    bitwise_and(hls, image, result);
    return;
}