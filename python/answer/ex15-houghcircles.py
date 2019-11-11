def imageProcessing(image): 
    result = imageCopy(image)
    result = convertColor(result, cv2.COLOR_BGR2GRAY)
    circles = houghCircles(result, cv2.HOUGH_GRADIENT, 1, 40+1, 100+1, 80+1, 25, 0)
    result = drawHoughCircles(image, circles)
    return result