import numpy as np
import cv2

cap = cv2.VideoCapture('drop.avi')

if not cap.isOpened():
  print "Error when reading image file"

def on_mouse(event, x, y, flags, params):
    if event == cv2.cv.CV_EVENT_LBUTTONDOWN:
         print 'Start Mouse Position: '+str(x)+', '+str(y)
         sbox = [x, y]

while(cap.isOpened()):
    ret, frame = cap.read()

    cv2.putText(frame,
    str(cap.get(cv2.cv.CV_CAP_PROP_POS_FRAMES)),
    (25, 50),
    cv2.FONT_HERSHEY_SIMPLEX,
    2,
    255)

    cv2.namedWindow('frame')
    cv2.cv.SetMouseCallback('frame', on_mouse, 0)
    cv2.imshow('frame',frame)
    while not cv2.waitKey(2555904):
        pass

cap.release()
cv2.destroyAllWindows()