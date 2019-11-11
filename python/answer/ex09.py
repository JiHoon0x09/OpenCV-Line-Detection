def imageProcessing(image): 
    result = imageCopy(image)
    result = convertColor(result, cv2.COLOR_BGR2GRAY)
    MORPH_CROSS = imageMorphologyKernel(cv2.MORPH_CROSS, 5)
    result = imageMorphologyEx(result, cv2.MORPH_GRADIENT , MORPH_CROSS)
    return result