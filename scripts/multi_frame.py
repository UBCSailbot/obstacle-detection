import cv2
import copy
import sys



def main(argv):
    if len(sys.argv) != 2:
        print "Usage: main.py <file name>"
        sys.exit()

    cap = cv2.VideoCapture(sys.argv[1])

    if not cap.isOpened():
      print "Error when reading image file"

    previous_frame = None

    while(cap.isOpened()):
        ret, frame = cap.read()

        if previous_frame is not None:
            result = cv2.absdiff(frame, previous_frame)
            cv2.imshow('frame', result)
        previous_frame = copy.copy(frame)

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    cap.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
   main(sys.argv[1:])