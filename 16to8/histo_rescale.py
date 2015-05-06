import cv2
import sys, os
z
from shutil import rmtree

def convert_to_video(top_dir, temp_dir):
    cmd = "ffmpeg -i \"" + temp_dir + "/img_%06d.png\" -r 24 -vf \"transpose=2\" " + top_dir + "/out_histo1.avi"
    print cmd
    os.system(cmd)

def histeq(im,nbr_bins=256):

   #get image histogram
   imhist,bins = np.histogram(im.flatten(),nbr_bins,normed=False)
   cdf = imhist.cumsum() #cumulative distribution function
   cdf = (nbr_bins-1) * cdf / cdf[-1] #normalize

   #use linear interpolation of cdf to find new pixel values
   im2 = np.interp(im.flatten(),bins[:-1],cdf)

   return im2.reshape(im.shape), cdf

def scale_16to8(img, img_min=0, img_max=0):
    if img_min or img_max:
        img = img.clip(img_min, img_max - 1)
        img -= img_min
    else:
        img_min = float(img.min())
        img_max = float(img.max())
        img -= img_min
        img *= 255.0 / (img_max - img_min)

    img = img.astype(np.uint8)

    return img

input_dir = sys.argv[1]
output_dir = sys.argv[2]
temp_dir = os.path.join(output_dir, "tmp")
try:
    os.makedirs(temp_dir)
except OSError:
    pass

for file_name in os.listdir(input_dir):
    img = cv2.imread( os.path.join(input_dir, file_name), -1 )
    try:
#        img,cdf = histeq(img, pow(2,14))
        img = scale_16to8(img, 7360, 7615)    
        cv2.imwrite( os.path.join(temp_dir, file_name), img)

    except AttributeError:
        print "Failed to process " + file_name + ", skipping it."

#    img = cv2.resize(img, (0,0), fx=8, fy=8, interpolation=cv2.INTER_NEAREST)
#    cv2.imshow('window', img)
#    cv2.waitKey(0)
   
convert_to_video(output_dir, temp_dir) 
rmtree(temp_dir)
    
