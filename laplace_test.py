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


    for fname in file_list:
        img = cv2.imread(os.path.join(input_dir, fname))

        laplace = cv2.Laplacian(img, 8, ksize=3)
        dest_name = os.path.join(output_dir,
                                 fname.split('.')[0] + "-laplace3.jpg")
        cv2.imwrite(dest_name, laplace)

if __name__ == "__main__":
    __main__(argv)