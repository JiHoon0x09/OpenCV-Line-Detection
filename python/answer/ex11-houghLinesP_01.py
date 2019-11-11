def imageProcessing(image): 
    result = imageCopy(image)
    result = convertColor(result, cv2.COLOR_BGR2GRAY)
    result = cannyEdge(result, 100, 200)
    height, width = result.shape[:2]
    pt1 = (int(width*0.35), int(height*0.65))
    pt2 = (int(width*0.65), int(height*0.65))
    pt3 = (int(width*1.0), int(height*1.0))
    pt4 = (int(width*0.0), int(height*1.0))
    roi = np.array([[pt1, pt2, pt3, pt4]], dtype=np.int32)
    result = polyROI(result, roi)
    lines = houghLinesP(result, 1.0, np.pi/180, 50, 10, 50)
    result = drawHoughLinesP(image, lines)
    return result