import numpy as np
import cv2

cap = cv2.VideoCapture('drop.avi')
start_position = (0, 0)

if not cap.isOpened():
  print "Error when reading image file"

def on_mouse(event, x, y, flags, frame):
    if event == cv2.cv.CV_EVENT_LBUTTONDOWN:
        global start_position
        print 'Start Mouse Position: '+str(x)+', '+str(y)
        start_position = (x, y)
         
    elif event == cv2.cv.CV_EVENT_LBUTTONUP:
        global start_position
        print 'End Mouse Position: '+str(x)+', '+str(y)
        cv2.rectangle(frame, start_position, (x, y), (0,0,255), 1)
        cv2.imshow('frame',frame)

while(cap.isOpened()):
    ret, frame = cap.read()

    cv2.putText(frame,
    str(cap.get(cv2.cv.CV_CAP_PROP_POS_FRAMES)),
    (25, 50),
    cv2.FONT_HERSHEY_SIMPLEX,
    2,
    (255, 0, 0))

    cv2.namedWindow('frame')
    cv2.cv.SetMouseCallback('frame', on_mouse, frame)
    cv2.imshow('frame',frame)

    k=-1
    while k not in (27, ord('u'), ord('n'), 2555904):
	    k = cv2.waitKey(0)

    if k==27:    # Esc key to stop
        break
    elif k==ord('u'):
        print "undefined"
        continue
    elif k==ord('n'):
        print "nothing interesting"
        continue
    elif k==2555904:  # right arrow
        continue

cap.release()
cv2.destroyAllWindows()