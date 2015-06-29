import numpy as np
import cv2
import copy
import sys

ROIs = set()
start_position = None

def on_mouse(event, x, y, flags, frame):
    frameRect = copy.copy(frame)
    global start_position
    if event == cv2.cv.CV_EVENT_LBUTTONDOWN:
        print 'Start Left Mouse Position: '+str(x)+', '+str(y)
        start_position = (x, y)
         
    elif event == cv2.cv.CV_EVENT_LBUTTONUP:
        print 'End Left Mouse Position: '+str(x)+', '+str(y)
        ROIs.add((start_position, (x, y)))
        for ROI in ROIs:
            cv2.rectangle(frameRect, ROI[0], ROI[1], (0,0,255), 1)
        cv2.imshow('frame',frameRect)

    elif event == cv2.cv.CV_EVENT_RBUTTONDOWN:
        print 'End Right Mouse Position: '+str(x)+', '+str(y)
        ROIs.clear()
        cv2.imshow('frame',frameRect)

def main(argv):
    if len(sys.argv) != 2:
        print "Usage: main.py <file name>"
        sys.exit()

    cap = cv2.VideoCapture(sys.argv[1])

    if not cap.isOpened():
      print "Error when reading image file"

    while(cap.isOpened()):
        ROIs.clear()
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
        while k not in (27, ord('u'), ord('n'), ord('s'), 2490368, 2621440, 2555904):
            k = cv2.waitKey(0)
            print str(k) + " was pressed"

        if k==27:    # Esc key to stop
            break
        elif k==ord('u'):
            print "undefined"
            continue
        elif k==ord('n'):
            print "nothing interesting"
            continue
        elif k==2490368: # up arrow for fast reverse
            cap.set(cv2.cv.CV_CAP_PROP_POS_FRAMES, cap.get(cv2.cv.CV_CAP_PROP_POS_FRAMES) - 25)
        elif k==2621440: # down arrow for fast forward
            cap.set(cv2.cv.CV_CAP_PROP_POS_FRAMES, cap.get(cv2.cv.CV_CAP_PROP_POS_FRAMES) + 23)
        elif k==2555904: # right arrow for next frame
            continue

    cap.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
   main(sys.argv[1:])