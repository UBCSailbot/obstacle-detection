import os
import cv2
import numpy as np
import aux
from sys import argv


def __main__(args):
    input_dir = args[1]
    list_file = args[2]
    output_dir = args[3]

    file_list = aux.read_file_list(list_file)

    kernel = np.ones((3, 3), np.uint8)
    #kernel = cv2.getStructuringElement(cv2.MORPH_CROSS, (3, 3))

    for fname in file_list:
        img = cv2.imread(os.path.join(input_dir, fname))

        open = cv2.morphologyEx(img, cv2.MORPH_GRADIENT, kernel, iterations=1)
        dest_name = os.path.join(output_dir,
                                 fname.split('.')[0] + "-morphgrad1.jpg")
        cv2.imwrite(dest_name, open)

if __name__ == "__main__":
    __main__(argv)