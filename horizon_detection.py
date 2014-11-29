import cv2
import math
import os
import sys
import numpy as np

for file in os.listdir(os.path.dirname(sys.argv[0])):
	if file.endswith(".jpg"):
		img = cv2.imread(file)
		gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
		#cv2.imwrite("gray.jpg", gray)
		edges = cv2.Canny(gray, 80, 120)
		#cv2.imwrite("edge.jpg", edges)
		lines = cv2.HoughLinesP(edges, 1, np.pi/180, 100, None, 30, 12);
		longest_line = 0
		longest_points = ()
		try:
			for line in lines[0]:
				pt1 = (line[0],line[1])
				pt2 = (line[2],line[3])
				current_line = ((pt1[0]-pt2[0])**2+(pt1[1]-pt2[1])**2)
				if (current_line > longest_line):
					longest_line = current_line
					longest_points = (pt1, pt2)
			if (longest_line > 0):		
				cv2.line(img, longest_points[0], longest_points[1], (0,0,255), 3)
			cv2.imwrite(str(os.path.splitext(file)[0]) + " - horizon.jpg", img)
		except:
			pass