import sys, os
import cv2
import matplotlib.pyplot as plt
import numpy as np

#frame_dir = "/home/paul/Desktop/sailbot/expt/20150219_VIGIL/Ucluelet Testing/00pretest/150218070749/raw"
#frame_dir = "/home/paul/Desktop/sailbot/expt/20150219_VIGIL/Ucluelet Testing/01ferrydeck1/150218071503-HorizonFromTopOfFerry/raw"
#frame_dir = "/home/paul/Desktop/sailbot/expt/20150219_VIGIL/Ucluelet Testing/01ferrydeck1/150218072105-360_onFerryDeck/raw"
#frame_dir = "/home/paul/Desktop/sailbot/expt/20150219_VIGIL/Ucluelet Testing/01ferrydeck1/150218072144-Shaking on deck/raw"
#frame_dir = "/home/paul/Desktop/sailbot/expt/20150219_VIGIL/Ucluelet Testing/04ucluelet_day/150218102803-Sun Sparkles/raw"
#frame_dir = "/home/paul/Desktop/sailbot/expt/20150219_VIGIL/Ucluelet Testing/04ucluelet_day/150218103647-Buoy/raw"

def indexof_densest_level(histo_vals):
	max_density = 0
	max_index = 0

	for i in range(histo_vals.size):
		clipped = histo_vals[i:i + 256]
		density = sum(clipped)
		if density > max_density:
			max_density = density
			max_index = i

	return max_index + 128

def get_name_from_frames_dir(f):
	head, raw_dir = os.path.split(f)
	head, timestamp = os.path.split(head)
	head, session_dir = os.path.split(head)
	return session_dir + timestamp

frame_dir = sys.argv[1]

save_name = get_name_from_frames_dir(frame_dir)

pixels = []
levels = []
avgs = []

for img_file in os.listdir(frame_dir):

#	print "Reading " + os.path.join(frame_dir, img_file)

	if not img_file.endswith(".png"):
		print "Detected non-image file! " + img_file
		continue
	
	#print "Reading image"
	img = cv2.imread( os.path.join(frame_dir, img_file), -1 )
	#print "Adding image to array"
	try:
		pixels += img.flat
	except AttributeError:
		print "Image read failed. Skipping " + img_file

	"""
	print "Binning current image"
	histo_vals, bins, patches = plt.hist(img.flat, img.max() - img.min())

	# Find the 256-value window that fits the greatest number of pixels
	print "Finding densest window"
	densest_level_index = indexof_densest_level(histo_vals)
	levels.append( bins[densest_level_index] )

	#plt.vlines(max_base + 128, 0, histo_vals.max(), color='green', 
	#	label="avg: " + str(max_base+128))

	# Plot the weighted average of that window
	print "Calculating weighted average of window"
	clipped = histo_vals[densest_level_index - 128:densest_level_index + 128]
	base_intensity_val = bins[densest_level_index - 128]
	weighted_avg = int( np.average(range(256), weights=clipped) + base_intensity_val )

	avgs.append(weighted_avg)
	"""

"""
avg_level = np.mean(levels)
stdev_level = np.std(levels)

avg_weighted_avg = np.mean(avgs)
stdev_weighted_avg = np.std(avgs)

print ""
print "Average level: " + str(avg_level)
print "StdDev of level: " + str(stdev_level)
print "Average weighted avg: " + str(avg_weighted_avg)
print "StdDev of weighted avg: " + str(stdev_weighted_avg)
"""

#print len(pixels)
#print max(pixels) - min(pixels)

print "Done reading frames for " + save_name

max_pixel = int(max(pixels))
min_pixel = int(min(pixels))

histo_vals, bins, patches = plt.hist(pixels, max_pixel - min_pixel)

densest_level_index = indexof_densest_level(histo_vals)
clipped = histo_vals[densest_level_index - 128:densest_level_index + 128]

base_intensity_val = int(bins[densest_level_index - 128])
top_intensity_val = int(bins[densest_level_index + 128])

plt.vlines([base_intensity_val, top_intensity_val], 0, histo_vals.max(), color='red', 
	label=str.format("Densest 8-bit\nwindow\nmin: {0}\nmax: {1}", base_intensity_val, top_intensity_val))

weighted_avg = int( np.average(range(256), weights=clipped) + base_intensity_val )
plt.vlines(weighted_avg, 0, histo_vals.max(), color='green',
	label="weighted\navg: " + str(weighted_avg))

save_dir, tail = os.path.split(frame_dir)

plt.legend(loc='center left', bbox_to_anchor=(1, 0.5))
plt.title("Histogram of pixel values\n" + save_name)
plt.xlabel("Lepton pixel intensity values")

plt.text(min_pixel, 0, str(min_pixel), 
	verticalalignment='bottom', horizontalalignment='right')
plt.text(max_pixel, 0, str(max_pixel), 
	verticalalignment='bottom', horizontalalignment='left')

plt.savefig(os.path.join(save_dir, save_name) + ".png", bbox_inches='tight')

fig = plt.gcf()
fig.canvas.set_window_title(save_name)
#plt.show()
