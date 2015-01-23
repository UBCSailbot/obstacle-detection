__author__ = 'paul'

import os
import cv2
import numpy as np
import auxiliary
from sys import argv


def __main__(args):
    input_dir = args[1]
    list_file = args[2]
    output_dir = args[3]

    file_list = auxiliary.read_file_list(list_file)


    for fname in file_list:
        img = cv2.imread(os.path.join(input_dir, fname))
        img = np.float32(img)

        corners = cv2.cornerHarris(img, 2, 3, 0.04)
        dest_name = os.path.join(output_dir,
                                 fname.split('.')[0] + "-corners.jpg")
        cv2.imwrite(dest_name, corners)

if __name__ == "__main__":
    __main__(argv)