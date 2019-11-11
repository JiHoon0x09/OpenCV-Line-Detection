def lineFitting(image, lines, color = (0,0,255), thickness = 3, slope_threshold = (5. * np.pi / 180.)):
    result = imageCopy(image)
    height = image.shape[0]
    lefts, rights = splitTwoSideLines(lines, slope_threshold)
    left = medianPoint(lefts)
    right = medianPoint(rights)
    min_y = int(height*0.6)
    max_y = height
    if left is not None:
        min_x_left = interpolate(left[1], left[2], left[3], left[4], min_y)
        max_x_left = interpolate(left[1], left[2], left[3], left[4], max_y)
        cv2.line(result, (min_x_left, min_y), (max_x_left, max_y), color, thickness)
    if right is not None:
        min_x_right = interpolate(right[1], right[2], right[3], right[4], min_y)
        max_x_right = interpolate(right[1], right[2], right[3], right[4], max_y)
        cv2.line(result, (min_x_right, min_y), (max_x_right, max_y), color, thickness)
    return result
