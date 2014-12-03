"""
A module with auxiliary helper functions
used across multiple other modules.
"""


def read_file_list(file_list):
    text = open(file_list).readlines()
    paths = []
    for fname in text:
        if len(fname.strip()) > 0:
            #paths.append(path.join(input_dir, fname.strip()))
            paths.append(fname.strip())
    return paths


def paint(img):
    import cv2
    cv2.imshow('image', img)
    cv2.waitKey(0)
    cv2.destroyAllWindows()