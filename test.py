import numpy as np
import cv2
from multiprocessing import Process
import gi
gi.require_version('Gst', '1.0')
from gi.repository import Gst
cap = cv2.VideoCapture(-1)

# Define the codec and create VideoWriter object
# out = cv2.VideoWriter('appsrc ! queue ! videoconvert ! video/x-raw ! omxh264enc ! video/x-h264 ! h264parse ! rtph264pay ! udpsink host=192.168.0.6 port=5000 sync=false',0,25.0,(640,480))
#out = cv2.VideoWriter('appsrc ! videoconvert ! shmsink socket-path=/tmp/foo sync=true wait-for-connection=false shm-size=10000000',0,25.0,(640,480))

framerate = 25.0
# out = cv2.VideoWriter('appsrc ! videoconvert ! ' 'x264enc noise-reduction=10000 speed-preset=ultrafast tune=zerolatency ! ' 'rtph264pay config-interval=1 pt=96 !'                  'tcpserversink host=192.168.0.6 port=5000 sync=false', 0, framerate, (640, 480))

out = cv2.VideoWriter('appsrc ! videoconvert ! '
                         'h264parse ! '
                         'rtph264pay config-interval=1 pt=96 !'
                         'tcpserversink host=192.168.0.6 port=5000 sync=false',
                         0, framerate, (640, 480))


while cap.isOpened():
    ret, frame = cap.read()
    if ret:
        frame = cv2.flip(frame, 0)
        frame = cv2.Canny(frame, 50, 100)

        cv2.imshow("canny", frame)
        # write the flipped frame
        out.write(frame)

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
    else:
        break

# Release everything if job is finished
cap.release()
out.release()
cv2.destroyAllWindows()