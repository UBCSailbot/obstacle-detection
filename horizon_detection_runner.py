import cv2
import math
import os
import sys
import numpy as np
import horizon_detection
import aux

#horizon_test.py input_dir file_list output_dir
#config.txt contains dir of input image/output image

def __main__(sys.argv):
	input_dir = sys.argv[1]
	list_file = sys.argv[2]
	output_dir = sys.argv[3]

    file_list = read_file_list(file_list, input_dir)
    for line in file_list:
        try:
            img = cv2.imread(line)
            img = img[24:239, 0:277] #comment this line out if no cropping is needed
            horizon_line(img)
            cv2.imwrite(os.path.join(output_dir, str(os.path.splitext(file)[0])) + " - horizon.jpg", img)
        except:
        	print "something failed"

if __name__ == "__main__":
    __main__(sys.argv)