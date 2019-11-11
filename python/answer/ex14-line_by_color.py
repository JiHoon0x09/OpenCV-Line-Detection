def imageProcessing(image): 
    result = imageCopy(image)
    height, width = result.shape[:2]
    pt1 = (width*0.45, height*0.6)
    pt2 = (width*0.55, height*0.6)
    pt3 = (width*0.85, height*0.9)
    pt4 = (width*0.15, height*0.9)
    roi_corners = np.array([[pt1, pt2, pt3, pt4]], dtype=np.int32)
    result = polyROI(result, roi_corners)
    hls = convertColor(result, cv2.COLOR_BGR2HLS)
    white_lower = np.array([0, 180, 0])
    white_upper = np.array([180, 255, 255])
    white = rangeColor(hls, white_lower, white_upper)
    yellow_lower = np.array([10, 140, 100])
    yellow_upper = np.array([35, 200, 255])
    yellow = rangeColor(hls, yellow_lower, yellow_upper)
    result = white + yellow
    MORPH_CROSS = imageMorphologyKernel(cv2.MORPH_CROSS, 3)
    result = imageMorphologyEx(result, cv2.MORPH_CLOSE, MORPH_CROSS)
    result = imageMorphologyEx(result, cv2.MORPH_GRADIENT, MORPH_CROSS)
    result = cannyEdge(result, 100, 200)
    lines = houghLinesP(result, 1, np.pi/180, 30, 20, 50)
    result = lineFitting(image, lines, (0, 0, 255), 5, 5. * np.pi / 180.)
    return result