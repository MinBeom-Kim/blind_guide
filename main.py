import numpy as np
import cv2
import time

# cap = cv2.VideoCapture('http://113.198.244.122:8090/?action=stream')
#cap = cv2.VideoCapture('rtsp://113.198.244.122:8554/test')
# cap = cv2.VideoCapture('./src/test_04.mp4')
cap = cv2.VideoCapture('udpsrc port=5000 caps = "application/x-rtp, media=(string)video, clock-rate=(int)90000, encoding-name=(string)H264, payload=(int)96" ! rtph264depay ! decodebin ! videoconvert ! appsink', cv2.CAP_GSTREAMER)

while(cap.isOpened()):
    
    kernel = np.ones((16, 16), np.uint8)

    ret, cap_frame = cap.read()

    #gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    #cv2.GaussianBlur(frame, (7, 7), 1.5)
    frame = cv2.Canny(cap_frame, 50, 100)
    #cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (16, 16))
    #cv2.morphologyEx(frame, cv2.MORPH_CLOSE, (16, 16))

    ret,frame_result1 = cv2.threshold(frame, 127, 255, cv2.THRESH_BINARY)

    #ret, frame_result2 = cv2.threshold(frame, 0, 255, cv2.THRESH_BINARY+cv2.THRESH_OTSU)

    #frame_blur = cv2.GaussianBlur(frame, (5,5), 0)
    #ret, frame_result3 = cv2.threshold(frame_blur, 0, 255, cv2.THRESH_BINARY+cv2.THRESH_OTSU)


    time.sleep(0.035)

    cv2.imshow("SOURCE", cap_frame)
    cv2.imshow("THRESH_BINARY", frame_result1)
    #cv2.imshow("THRESH_OTSU", frame_result2)
    #cv2.imshow("THRESH_OTSU + Gaussian filtering", frame_result3)


    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
