import cv2
import math
import os
import sys

for file in os.listdir(os.path.dirname(sys.argv[0])):
	if file.endswith(".jpg"):
		img = cv2.imread(file)
		gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
		edges = cv2.Canny(gray, 80, 120)
		lines = cv2.HoughLinesP(edges, 1, math.pi/2, 2, None, 30, 1);
		for line in lines[0]:
			pt1 = (line[0],line[1])
			pt2 = (line[2],line[3])
			cv2.line(img, pt1, pt2, (0,0,255), 3)
		cv2.imwrite("horizon - " + os.path.splitext(file)[0], img)