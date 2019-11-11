from OpenCV_Functions import *
def imageProcessing2(image):
    result = imageCopy(image) 
    resultcolor = convertColor(image, cv2.COLOR_BGRA2BGR)

    result = convertColor(result, cv2.COLOR_BGR2GRAY)
    result = cannyEdge(result, 100, 200)
    h, w = result.shape[:2]
    sp1 = [int(w*0.4), int(h*0.65)]
    sp2 = [int(w*0.6), int(h*0.65)]
    sp3 = [int(w*1.0), int(h*1.0)]
    sp4 = [int(w*0.0), int(h*1.0)]
    dp1 = [int(w*0.1), 0]
    dp2 = [int(w*0.9), 0]
    dp3 = [int(w*0.9), h]
    dp4 = [int(w*0.1), h]
    spts = np.float32([sp1,sp2,sp3,sp4])
    dpts = np.float32([dp1,dp2,dp3,dp4])

    result = imagePerspectiveTransformation(result, spts, dpts)


    lines = houghLinesP(result, 1, np.pi/180, 100)
    emtpy = np.zeros((h, w), np.uint8)
    result = drawHoughLinesP(emtpy, lines)


    cv2.namedWindow("result",cv2.WINDOW_GUI_EXPANDED)
    cv2.imshow("result",result)
    result = imagePerspectiveTransformation(result, dpts, spts)
    result = addImage(result, resultcolor)
    return result
    
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
