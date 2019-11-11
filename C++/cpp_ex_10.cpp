void imageProcessing(Mat &image, Mat &result)
{
    result = imageCopy(image);
    Mat cross;
    imageMorphologyKernel(cross, MORPH_CROSS, 3);
    imageMorphologyEx(result, result, MORPH_GRADIENT, cross);
    convertColor(result, result, COLOR_BGR2GRAY);
    imageThreshold(result, result, 50, 255, THRESH_BINARY);
    return;
}