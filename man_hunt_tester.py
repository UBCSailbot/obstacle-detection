from sys import argv
import man_hunt
import aux
from cv2 import imread

__author__ = 'paul'


def __main__(args):
    dir_name = args[0]
    file_list = aux.read_file_list(args[1])
    for fname in file_list:
        img = imread(fname)
        #img = img[24:239, 0:277] #comment this line out if no cropping is needed
