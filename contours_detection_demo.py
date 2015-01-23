import numpy as np
import cv2

cap = cv2.VideoCapture(0)

while(True):
    ret, frame = cap.read()
    
    imgray = cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)
    #ret,thresh = cv2.threshold(imgray,127,255,0)
    edges = cv2.Canny(imgray, 100, 256)
    contours, hierarchy = cv2.findContours(edges,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)

    try:
        #draw box around object
        x,y,w,h = cv2.boundingRect(contours[0])
        cv2.rectangle(frame,(x,y),(x+w,y+h),(0,0,255),2)

        #draw ellipse around object
        ellipse = cv2.fitEllipse(contours[1])
        cv2.ellipse(frame,ellipse,(128,128,0),2)

        #outline first contour
        cv2.drawContours(frame, contours, 0, (0,255,0), 3)
        #fill in 3rd contour
        cv2.drawContours(frame, contours, 3, (255,0,0), -1)
    except:
        pass

    # Display the resulting frame
    cv2.imshow('frame',frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()

 
