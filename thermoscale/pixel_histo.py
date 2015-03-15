import sys, os
import cv2
import matplotlib.pyplot as plt
import numpy as np

PLOTFILE_FORMAT = ".png"

def densest_window_range(histo_vals):
    max_density = 0
    densest_base = 0

    for i in range(histo_vals.size):
        clipped = histo_vals[i:i + 256]
        density = sum(clipped)
        if density > max_density:
            max_density = density
            densest_base = i

    return (densest_base, densest_base + 256)


def get_name_from_frames_dir(f):
    head, raw_dir = os.path.split(f)
    head, timestamp = os.path.split(head)
    head, session_dir = os.path.split(head)
    return session_dir + timestamp
    
    
def concatenate_frames(frame_dir):
    pixels = np.array([])

    for img_file in os.listdir(frame_dir):

        if not img_file.endswith(".png"):
            print "Detected non-image file! " + img_file
            continue
    
        img = cv2.imread( os.path.join(frame_dir, img_file), -1 )
        try:
            pixels = np.concatenate([pixels, img.flat])
        except AttributeError:
            print "Image read failed. Skipping " + img_file
    
    return pixels


def plot_densest_window_range(histo_vals, bins):
    window_range = densest_window_range(histo_vals)
    window_minval = int(bins[window_range[0]])
    window_maxval = int(bins[window_range[1]])

    # Plot the min and max of that 256-range window
    plt.vlines([window_minval, window_maxval], 0, histo_vals.max(),
        color='red', label=str.format(
            "Densest 8-bit\nwindow\nmin: {0}\nmax: {1}", window_minval, window_maxval))

    #Plot the average value within that 256-range window
    clipped = histo_vals[window_range[0]:window_range[1]]
    window_avg = int( np.average(range(256), weights=clipped) + window_minval )
    plt.vlines(window_avg, 0, histo_vals.max(), color='green',
        label="window\navg: " + str(window_avg))


def plot_min_max(min_pixel, max_pixel):
    min_pixel = int(min_pixel)
    max_pixel = int(max_pixel)
    plt.text(min_pixel, 0, str(min_pixel), 
        verticalalignment='bottom', horizontalalignment='right')
    plt.text(max_pixel, 0, str(max_pixel), 
        verticalalignment='bottom', horizontalalignment='left')

def plot_video_stats(pixels):

    # Generate histogram of pixel values over entire video
    histo_vals, bins, patches = plt.hist(pixels, pixels.max() - pixels.min())

    # Find the 256-range window that contains the most pixels
    if len(histo_vals) > 256:
        plot_densest_window_range(histo_vals, bins)
    
    # Plot the global average pixel value throughout entire video
    total_avg = int(pixels.mean())
    plt.vlines(total_avg, 0, histo_vals.max(), color='magenta', 
        label="global\navg: " + str(total_avg))

    # Add legend and axes labels
    plt.legend(loc='center left', bbox_to_anchor=(1, 0.5))
    plt.xlabel("Lepton pixel intensity values")
    plot_min_max(pixels.min(), pixels.max())


def generate_save_path(frame_dir):
    save_dir, tail = os.path.split(frame_dir)
    return os.path.join(save_dir, get_name_from_frames_dir(frame_dir) + PLOTFILE_FORMAT)


def save_plot(frame_dir, save_name):
    plt.title("Histogram of pixel values\n" + save_name)
    plt.savefig(generate_save_path(frame_dir), bbox_inches='tight')
    plt.clf()


def generate_video_histo(frame_dir, overwrite_existing=True):
    
    save_name = get_name_from_frames_dir(frame_dir)
    if not overwrite_existing and os.path.exists(generate_save_path(frame_dir)):
        print "Overwrite set to false. Skipping " + save_name
        return

    pixels = concatenate_frames(frame_dir)
    print "Done reading frames for " + save_name

    plot_video_stats(pixels)
    save_plot(frame_dir, save_name)
    print "Done processing " + save_name


def main():
    frame_dir = sys.argv[1]
    generate_video_histo(frame_dir)

if __name__ == "__main__":
  main()
