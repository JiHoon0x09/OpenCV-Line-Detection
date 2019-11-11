from OpenCV_Functions import *
def imageProcessing2(image):
    result = np.copy(image)
    h, w = result.shape[:2]
    p1 = (int(w*0.35),int(h*0.65))
    p2 = (int(w*0.65),int(h*0.65))
    p3 = (int(w),int(h))
    p4 = (0, int(h))
    roiPoly = np.array([[p1,p2,p3,p4]], dtype=np.int32)
    
    roiActive = polyROI(result, roiPoly)
    roiDeactive = result - roiActive

    roiActive = imageMedianBlur(roiActive, 3)
    roiDeactive = imageBilateralFilter(roiDeactive, 3, 3, 3)
    result = addWeightedImage(roiDeactive, 80, roiActive, 100)
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
