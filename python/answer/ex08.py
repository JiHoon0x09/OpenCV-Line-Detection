def imageProcessing(image): 
    result = imageCopy(image)
    result = convertColor(result, cv2.COLOR_BGR2HSV)
    h, s, v = splitImage(result)
    v = histogramEqualize(v)
    v = imageThreshold(v, 128, 255, cv2.THRESH_BINARY)
    result = mergeImage(h, s, v)
    result = convertColor(result, cv2.COLOR_HSV2BGR)
    return result