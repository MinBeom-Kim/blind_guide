import time
import numpy as np
import cv2
from multiprocessing import Process
import gi
gi.require_version('Gst', '1.0')
from gi.repository import Gst

# Cam properties
fps = 30.
frame_width = 1920
frame_height = 1080
# Create capture
cap = cv2.VideoCapture(-1)

# Set camera properties
cap.set(cv2.CAP_PROP_FRAME_WIDTH, frame_width)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, frame_height)
cap.set(cv2.CAP_PROP_FPS, fps)

# Define the gstreamer sink
gst_str = "appsrc ! videoconvert ! shmsink socket-path=/tmp/foo sync=true wait-for-connection=false shm-size=10000000"


# Check if cap is open
if cap.isOpened() is not True:
    print("Cannot open camera. Exiting.")
    quit()

# Create videowriter as a SHM sink
out = cv2.VideoWriter(gst_str, 0, fps, (frame_width, frame_height), True)

# Loop it
while True:
    # Get the frame
    ret, frame = cap.read()
    # Check
    if ret is True:
        # Flip frame
        # frame = cv2.flip(frame, 1)
        frame = cv2.flip(frame, 0)
        frame = cv2.Canny(frame, 50, 100)

        cv2.imshow("canny", frame)
        # Write to SHM
        out.write(frame)

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
    else:
        print("Camera error.")
        time.sleep(10)

cap.release()
out.release()
cv2.destroyAllWindows()