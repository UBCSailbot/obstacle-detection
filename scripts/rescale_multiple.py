"""
Rescale an entire experiment directory & generate video from the rescaled frames.
"""

from rescale import rescale
from make_video import convert_to_video

def rescale_multiple(experiment_dir, horizon_file_name="imuLog.txt", options="--rescaling-type 3 --paint-horizon", description="rescaled_median_w1"):

	for root, dirs, files in os.walk(experiment_dir):
		if "raw" in dirs:
			raw_dir = os.path.join(root, "raw")
			output_dir = os.path.join(root, description)
			
			horizon_file_path = os.path.join(root, horizon_file_name)
			rescale(raw_dir, output_dir, options, horizon_file_path)

			video_path = os.path.join(root, description + ".avi")
			convert_to_video( output_dir, video_path)

def main():
	import os, sys

	if len(sys.argv) != 3:
		print "Usage: python {0} <experiment-dir> <horizon_file_name>".format(sys.argv[0])
		sys.exit()

	experiment_dir = sys.argv[1]
	horizon_file_name = sys.argv[2]

	rescale_multiple(experiment_dir, horizon_file_name)


if __name__ == "__main__":
	main()