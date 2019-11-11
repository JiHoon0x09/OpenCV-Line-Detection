def imageProcessing(image): 
    result = imageCopy(image)
    result = convertColor(result, cv2.COLOR_BGR2GRAY)
    result = cannyEdge(result, 100, 200)
    height, width = result.shape[:2]
    pt1 = (width*0.45, height*0.65)
    pt2 = (width*0.55, height*0.65)
    pt3 = (width, height*1.0)
    pt4 = (0, height*1.0)
    roi_corners = np.array([[pt1, pt2, pt3, pt4]], dtype=np.int32)
    result = polyROI(result, roi_corners)
    lines = houghLinesP(result, 1, np.pi/180, 40)
    result = lineFitting(image, lines, (0, 0, 255), 5, 5. * np.pi / 180.)
    return result