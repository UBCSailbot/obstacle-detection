from sys import argv
import man_hunt
import aux

__author__ = 'paul'


def __main__(sys.argv):
    dir_name = argv[0]
    file_list = aux.read_file_list(argv[1])
    img = cv2.imread(file)
        img = img[24:239, 0:277] #comment this line out if no cropping is needed
        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)