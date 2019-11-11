from OpenCV_Functions import *
def imageProcessing2(image):
    result = np.copy(image)
    result = convertColor(result,cv2.COLOR_BGR2GRAY)
    morph = imageMorphologyKernel(cv2.MORPH_CROSS, 5)
    result = imageMorphologyEx(result, cv2.MORPH_GRADIENT, morph)

    h, w = result.shape[:2]
    s_p1 = [int(w*0.42), int(h*0.65)]
    s_p2 = [int(w*0.58), int(h*0.65)]
    s_p3 = [int(w*1.0), int(h*1.0)]
    s_p4 = [int(w*0.0), int(h*1.0)]
    d_p1 = [int(w*0.1), 0]
    d_p2 = [int(w*0.9), 0]
    d_p3 = [int(w*0.9), h]
    d_p4 = [int(w*0.1), h]

    s_pts = np.float32([s_p1, s_p2, s_p3, s_p4])
    d_pts = np.float32([d_p1, d_p2, d_p3, d_p4])
    roadPoint = drawCircle(result, tuple(s_p1), 10, (255, 0, 0), -1)
    roadPoint = drawCircle(roadPoint, tuple(s_p2), 10, (0, 255, 0), -1)
    roadPoint = drawCircle(roadPoint, tuple(s_p3), 10, (0, 0, 255), -1)
    roadPoint = drawCircle(roadPoint, tuple(s_p4), 10, (255, 255, 0), -1)
    roadAffine_01 = imagePerspectiveTransformation(roadPoint, s_pts, d_pts) 
    roadAffine_03 = imagePerspectiveTransformation(roadAffine_01, d_pts, s_pts  )
    cv2.namedWindow("roadAffine1", cv2.WINDOW_GUI_EXPANDED)
    #cv2.namedWindow("roadAffine3", cv2.WINDOW_GUI_EXPANDED)
    cv2.imshow("roadAffine1",roadAffine_01)
    #cv2.imshow("roadAffine3",roadAffine_03)

    return roadPoint
    
def Video2(openpath, savepath = "output.avi"):
    cap = cv2.VideoCapture(openpath)
    if cap.isOpened():
        print("Video Opened")
    else:
        print("Video Not Opened")
        print("Program Abort")
        exit()
    fps = int(cap.get(cv2.CAP_PROP_FPS))
    width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
    height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
    fourcc = int(cap.get(cv2.CAP_PROP_FOURCC))
    out = cv2.VideoWriter(savepath, fourcc, fps, (width, height), True)
    cv2.namedWindow("Input", cv2.WINDOW_GUI_EXPANDED)
    cv2.namedWindow("Output", cv2.WINDOW_GUI_EXPANDED)
    import OpenCV_Functions
    while cap.isOpened():
        # Capture frame-by-frame
        ret, frame = cap.read()
        if ret:
            # Our operations on the frame come here
            output = imageProcessing2(frame)
            # Write frame-by-frame
            out.write(output)
            # Display the resulting frame
            cv2.imshow("Input", frame)
            cv2.imshow("Output", output)
        else:
            break
        # waitKey(int(1000.0/fps)) for matching fps of video
        if cv2.waitKey(int(1000.0/fps)) & 0xFF == ord('q'):
            break
    # When everything done, release the capture
    cap.release()
    out.release()
    cv2.destroyAllWindows()
    return

road_video_01 = "/home/opencv-mds/OpenCV_in_Ubuntu/Data/Lane_Detection_Videos/solidWhiteRight.mp4"

Video2(road_video_01, "output.mp4")
