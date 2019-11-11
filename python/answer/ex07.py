def imageProcessing(image): 
    result = imageCopy(image)
    height, width = result.shape[0], result.shape[1]
    pt1 = (int(width * 0.35), (int(height * 0.65))) 
    pt2 = (int(width * 0.65), (int(height * 0.65))) 
    pt3 = (int(width * 1.0), (int(height * 1.0))) 
    pt4 = (int(width * 0.0), (int(height * 1.0))) 
    roi_poly = np.array([[pt1, pt2, pt3, pt4]], dtype=np.int32)
    roi_active = polyROI(result, roi_poly)
    roi_deactive = result - roi_active
    roi_active = cannyEdge(roi_active, 100, 200)
    roi_deactive = convertColor(roi_deactive, cv2.COLOR_BGR2GRAY)
    result = addWeightedImage(roi_active, 100, roi_deactive, 100)
    return result