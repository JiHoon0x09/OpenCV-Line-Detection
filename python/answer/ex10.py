def imageProcessing(image): 
    result = imageCopy(image)
    result = convertColor(result, cv2.COLOR_BGR2GRAY)
    result = imageThreshold(result, 128, 255, cv2.THRESH_BINARY)
    MORPH_ELLIPSE = imageMorphologyKernel(cv2.MORPH_ELLIPSE, 5)
    result = imageMorphologyEx(result, cv2.MORPH_GRADIENT , MORPH_ELLIPSE)

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

    return result