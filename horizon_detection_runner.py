import os
from sys import argv
import horizon_detection
import auxiliary
import cv2

#horizon_test.py input_dir file_list output_dir
#config.txt doesn't exist yet, but will contain dir of input image/output image

def __main__(args):
    input_dir = args[1]
    list_file = args[2]
    output_dir = args[3]

    file_list = auxiliary.read_file_list(list_file)
    for fname in file_list:
        img = cv2.imread(os.path.join(input_dir, fname))
        img = img[24:239, 0:277]  # comment this line out if no cropping is needed
        edges, return_val = horizon_detection.horizon_line(img)
        if return_val == 0:
            print "No lines were found in " + fname + "."
        dest_name = os.path.join(output_dir,
                                 fname.split('.')[0] + "-horizon.jpg")
        edges_name = os.path.join(output_dir,
                                 fname.split('.')[0] + "-edges.jpg")
        cv2.imwrite(dest_name, img)
        cv2.imwrite(edges_name, edges)


if __name__ == "__main__":
    __main__(argv)