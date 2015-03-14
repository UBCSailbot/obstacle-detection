import os
import sys

import cv2
import numpy as np
import png

def find_max_min(img):
  rows, cols = img.shape
  max_pxl = 0
  min_pxl = pow(2,16)-1

  for i in range(rows):
    for j in range(cols):
      if img[i,j] > max_pxl:
        max_pxl = img[i,j]
      if img[i,j] < min_pxl:
        min_pxl = img[i,j]

  return (max_pxl, min_pxl)

def scale_img(img, max_pxl, min_pxl):
  rows, cols = img.shape
  downscaled = np.zeros((rows, cols), dtype=np.uint8)
  diff = max_pxl - min_pxl
  scale = diff / 255
  for i in range(rows):
    for j in range(cols):
      downscaled[i,j] = (img[i,j] - min_pxl) / scale
      if downscaled[i,j] > 255:
        print downscaled[i,j]
  return downscaled

if len(sys.argv) < 3:
  print "Usage: 16to8.py <input_dir> <output_dir>"
  sys.exit()
  
def copy_img(in_img, out_img):
  rows, cols = in_img.shape

  for i in range(rows):
    for j in range(cols):
        out_img[i,j] = img[i,j]

  return out_img

input_dir = sys.argv[1]
output_avi = sys.argv[2]

fourcc = cv2.cv.CV_FOURCC('X','V','I','D')
vid = cv2.VideoWriter(output_avi, fourcc, 27, (80,60))

for in_file in os.listdir(input_dir):
  img = cv2.imread(os.path.join(input_dir, in_file), -1)

#  max_pxl, min_pxl = find_max_min(img)
#  print max_pxl, min_pxl
  img *= 255.0/img.max()
  max_pxl, min_pxl = find_max_min(img)
  print max_pxl, min_pxl
  
  downscaled = np.array((60, 80, 1), dtype=np.uint8)
  downscaled = copy_img(img, downscaled)

  cv2.imshow('window', img)
  cv2.imwrite(in_file + "_n")
  cv2.waitKey(0)
  vid.write(img)

vid.release()
