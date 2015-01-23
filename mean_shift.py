import cv2
import pymeanshift as pms    #pymeanshift is not a part of opencv

original_image = cv2.imread("IR_0275.jpg")

(segmented_image, labels_image, number_regions) = pms.segment(original_image, spatial_radius=6, 
                                                              range_radius=4.5, min_density=50)
cv2.imwrite("IR_0275 - 2.jpg", segmented_image)

