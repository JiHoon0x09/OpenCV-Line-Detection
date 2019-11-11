def imageProcessing(image): 
    result = imageCopy(image)
    result = convertColor(result, cv2.COLOR_BGR2GRAY)
    imageShow("phase1", result)
    result = cannyEdge(result, 100, 200)
    imageShow("phase2", result)
    height, width = result.shape[:2]
    src_pt1 = [int(width*0.4), int(height*0.65)]
    src_pt2 = [int(width*0.6), int(height*0.65)]
    src_pt3 = [width, height]
    src_pt4 = [0, height]
    dst_pt1 = [int(width*0.1), 0]
    dst_pt2 = [int(width*0.9), 0]
    dst_pt3 = [int(width*0.9), height]
    dst_pt4 = [int(width*0.1), height]
    src_pts = np.float32([src_pt1, src_pt2, src_pt3, src_pt4])
    dst_pts = np.float32([dst_pt1, dst_pt2, dst_pt3, dst_pt4])
    result = imagePerspectiveTransformation(result, src_pts, dst_pts)
    imageShow("phase3", result)
    lines = houghLinesP(result, 1.0, np.pi/180, 50, 10, 50)
    result = makeBlackImage(result, True)
    result = drawHoughLinesP(result, lines)
    imageShow("phase4", result)
    result = imagePerspectiveTransformation(result, src_pts, dst_pts, flags=cv2.WARP_INVERSE_MAP)
    imageShow("phase5", result)
    result = addWeightedImage(image, 100, result, 100)   
    return result