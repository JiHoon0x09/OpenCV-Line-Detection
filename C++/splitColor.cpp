void splitColor(Mat &image, Mat &result, Scalar &min, Scalar &max) 
{
    Mat mask = imageCopy(image);
    rangeColor(mask, mask, min, max);
    convertColor(mask, mask, COLOR_GRAY2BGR);
    bitwise_and(image, image, result, mask);
    return;
}