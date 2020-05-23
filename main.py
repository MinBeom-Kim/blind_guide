import numpy as np
import cv2

capt = cv2.VideoCapture('./src/test_04.mp4')

while(cap.isOpened()):
    
    kernel = np.ones((16, 16), np.uint8)

    ret, frame = cap.read()

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    cv2.GaussianBlur(cap, (7, 7), 1.5)
    cap = cv2.Canny(cap, 50, 100)
    cv2.getStructuringElement(cv2.MORPH_ELLIPSE, kernel)
    cv2.morphologyEx(cap, cv2.MORPH_CLOSE, kernel)

    ret,cap_result1 = cv2.threshold(cap, 127, 255, cv2.THRESH_BINARY)

    ret, cap_result2 = cv2.threshold(cap, 0, 255, cv2.THRESH_BINARY+cv2.THRESH_OTSU)

    cap_blur = cv2.GaussianBlur(cap, (5,5), 0)
    ret, cap_result3 = cv2.threshold(cap_blur, 0, 255, cv2.THRESH_BINARY+cv2.THRESH_OTSU)

    cv2.imshow("SOURCE", cap)
    cv2.imshow("THRESH_BINARY", cap_result1)
    cv2.imshow("THRESH_OTSU", cap_result2)
    cv2.imshow("THRESH_OTSU + Gaussian filtering", cap_result3)


    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
