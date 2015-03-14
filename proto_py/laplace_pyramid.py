__author__ = 'paul'

import cv2
import numpy as np,sys

A = cv2.imread('/home/paul/Desktop/vision/ir/gray/IR_0341.jpg')

G = A.copy()
gpA = [G]
for i in xrange(6):
    G = cv2.pyrDown(G)
    gpA.append(G)

lpA = [gpA[5]]
for i in xrange(5,0,-1):
    GE = cv2.pyrUp(gpA[i])
    L = cv2.subtract(gpA[i-1],GE)
    lpA.append(L)
    cv2.imshow('image',L)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

