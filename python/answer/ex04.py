from OpenCV_Functions import *

def imageProcessing2(image):
    result = imageCopy(image)
    pt1 = (430, 310)
    pt2 = (530, 310)
    pt3 = (940, 540)
    pt4 = (20, 540)
    result = drawLine(result, pt1, pt2, (255, 0, 0), 5)
    result = drawLine(result, pt2, pt3, (255, 0, 0), 5)
    result = drawLine(result, pt3, pt4, (255, 0, 0), 5)
    result = drawLine(result, pt4, pt1, (255, 0, 0), 5)
    height = image.shape[0]
    width = image.shape[1]
    pt1 = (int(width * 0.5), int(height * 0.5))
    pt2 = (int(width), int(height))
    pt3 = (0, height)
    result = drawLine(result, pt1, pt2, (0, 255, 0), 5)
    result = drawLine(result, pt2, pt3, (0, 255, 0), 5)
    result = drawLine(result, pt3, pt1, (0, 255, 0), 5)
    pt1 = (0,0)
    pt2 = (width, height)
    result = drawRect(result, pt1, pt2, (0, 0, 0), 5)
    pt1 = (int(width * 0.5), int(height * 0.5))
    result = drawCircle(result, pt1, 3, (255, 255, 255), -1)

    return result

def Video2(openpath, savepath = "output.avi"):
    cap = cv2.VideoCapture(openpath)
    if cap.isOpened():
        print("Video Opened")
    else:
        print("Video Not Opened")
        print("Program Abort")
        exit()
    fps = cap.get(cv2.CAP_PROP_FPS)
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
