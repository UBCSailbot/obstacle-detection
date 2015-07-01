import cv2
import copy
import sys
import collections
import logWrite
import constant

frame_metadata = {}
ROIs = set()
start_position = None

def on_mouse(event, x, y, flags, frame):
    frameRect = copy.copy(frame)
    global start_position
    if event == cv2.cv.CV_EVENT_LBUTTONDOWN:
        #print 'Start Left Mouse Position: '+str(x)+', '+str(y)
        start_position = (x/constant.RESCALE_FACTOR, y/constant.RESCALE_FACTOR)
         
    elif event == cv2.cv.CV_EVENT_LBUTTONUP:
        #print 'End Left Mouse Position: '+str(x)+', '+str(y)
        ROIs.add((start_position, (x/constant.RESCALE_FACTOR, y/constant.RESCALE_FACTOR)))
        for ROI in ROIs:
            start = tuple([constant.RESCALE_FACTOR*x for x in ROI[0]])
            end = tuple([constant.RESCALE_FACTOR*x for x in ROI[1]])
            cv2.rectangle(frameRect, start, end, (0,0,255), 1)
        cv2.imshow('frame',frameRect)

    elif event == cv2.cv.CV_EVENT_RBUTTONDOWN:
        #print 'End Right Mouse Position: '+str(x)+', '+str(y)
        ROIs.clear()
        cv2.imshow('frame',frameRect)

def main(argv):
    if len(sys.argv) != 2:
        print "Usage: main.py <file name>"
        sys.exit()

    cap = cv2.VideoCapture(sys.argv[1])

    if not cap.isOpened():
      print "Error when reading image file"

    log = logWrite.logWrite()
    log.new(str(sys.argv[1]))

    while(cap.isOpened()):
        ROIs.clear()
        ret, frame = cap.read()

        if int(cap.get(cv2.cv.CV_CAP_PROP_POS_FRAMES)) == cap.get(cv2.cv.CV_CAP_PROP_FRAME_COUNT):
            break

        frame = cv2.resize(frame, (0,0), fx=constant.RESCALE_FACTOR, fy=constant.RESCALE_FACTOR, interpolation=cv2.INTER_NEAREST)
        cv2.putText(frame,
        str(int(cap.get(cv2.cv.CV_CAP_PROP_POS_FRAMES))),
        (25, 50),
        cv2.FONT_HERSHEY_SIMPLEX,
        2,
        (255, 0, 0))

        cv2.namedWindow('frame')
        cv2.cv.SetMouseCallback('frame', on_mouse, frame)
        cv2.imshow('frame',frame)

        k=-1
        while k not in (chr(27), 'u', 'n', 's', 'w', 's', 'a', 'd'):
            k = chr(cv2.waitKey(0) & 255)
            print k + " was pressed"

        if k==chr(27):    # Esc key to stop
            break
        elif k=='u':
            ROIs.clear()
            frame_metadata[int(cap.get(cv2.cv.CV_CAP_PROP_POS_FRAMES))] = "undefined"
            print "undefined"
        elif k=='n':
            ROIs.clear()
            frame_metadata[int(cap.get(cv2.cv.CV_CAP_PROP_POS_FRAMES))] = "nothing interesting"
            print "nothing interesting"
        elif k=='w':
            cap.set(cv2.cv.CV_CAP_PROP_POS_FRAMES, int(cap.get(cv2.cv.CV_CAP_PROP_POS_FRAMES)) - constant.FRAME_SKIP + 1)
        elif k=='s':
            cap.set(cv2.cv.CV_CAP_PROP_POS_FRAMES, int(cap.get(cv2.cv.CV_CAP_PROP_POS_FRAMES)) + constant.FRAME_SKIP - 1)
        elif k=='a':
            cap.set(cv2.cv.CV_CAP_PROP_POS_FRAMES, int(cap.get(cv2.cv.CV_CAP_PROP_POS_FRAMES)) - 2)
        elif k=='d':
            pass

        if len(ROIs) > 0:
            frame_metadata[int(cap.get(cv2.cv.CV_CAP_PROP_POS_FRAMES))] = tuple(ROIs)

    log.write(collections.OrderedDict(sorted(frame_metadata.items(), key=lambda t: t[0])))
    log.close()

    cap.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
   main(sys.argv[1:])