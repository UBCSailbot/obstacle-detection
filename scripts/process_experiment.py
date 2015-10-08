"""
This script does the following for an entire experiment directory:

  1. Re-calibrates IMU log files using a config file located at the top of the experiment directory
  2. Run rescaling using the new logfiles, with the horizon painted on
  3. Compile the rescaled frames (with horizon painted on) into a video
  4. Delete the rescaled frames (with horizon painted on)
  5. Run rescaling again without the horizon painted on. These can be kept as a normalized version of the raw frames.

Uses a config file to specify what to do for every capture directory within the experiment directory. The config file is assumed to be at the top of the experiment directory.
"""

import adjust_imu_logfile
import rescale
import make_video
import shared

import sys, os
from shutil import rmtree

from ast import literal_eval

class Config:
	pass

def config_or_default(config_dict, field_name, default_value):
	try:
		return config_dict[field_name]
	except:
		return default_value

def parse_boolean(bool_string):
	return literal_eval(bool_string.capitalize())

def parse_config(config_file):
	config_dict = { line.strip().split('=')[0] : line.strip().split('=')[1] for line in open(config_file, 'r').readlines() if not line.isspace() and not line.startswith('#') }

	config = Config()

	config.roll_offset = float(config_or_default(config_dict, 'roll-offset', 0))
	config.pitch_offset = float(config_or_default(config_dict, 'pitch-offset', 0))
	config.invert_roll = parse_boolean(config_or_default(config_dict, 'invert-roll', False))
	config.invert_pitch = parse_boolean(config_or_default(config_dict, 'invert-pitch', False))

	# rescaling options
	rescaling_type = int(config_or_default(config_dict, 'rescaling-type', 3))
	smoothing_window = int(config_or_default(config_dict, 'smoothing-window', 1))
	config.rescaling_options = "--rescaling-type {0} --smoothing-window {1}".format(rescaling_type, smoothing_window)
	config.rescaling_desc = '_'.join([rescale.rescaling_types[rescaling_type - 1], 'w' + str(smoothing_window) ])

	# video options
	config.frame_rate = int(config_or_default(config_dict, 'framerate-fps', 9))
	config.rotate_frames = parse_boolean(config_or_default(config_dict, 'rotate-frames', False))

	return config


def adjust_imu_logfile_wrapper(capture_dir, config):
	logfile_path = os.path.join(capture_dir, shared.default_imu_output_file)
	adjust_imu_logfile.adjust_imu_logfile(logfile_path, config.roll_offset, config.pitch_offset, invert_roll=config.invert_roll, invert_pitch=config.invert_pitch)

def rescale_wrapper(capture_dir, rescaled_dir_name, config, paint_horizon=False):
	raw_dir = os.path.join(capture_dir, 'raw')
	output_dir = os.path.join(capture_dir, rescaled_dir_name)
	orientation_file = os.path.join(capture_dir, shared.default_imu_output_file_adjusted)

	rescaling_options = config.rescaling_options

	if paint_horizon:
		rescaling_options = shared.conditional_concat(rescaling_options, " --paint-horizon")

	rescale.rescale(raw_dir, output_dir, options=rescaling_options, orientation_file=orientation_file)

def make_video_wrapper(capture_dir, config):
	frame_dir = os.path.join(capture_dir, 'temp')
	video_file = os.path.join(capture_dir, config.rescaling_desc + '.avi')

	make_video.convert_to_video(frame_dir, video_file, config.frame_rate, rotate=config.rotate_frames)


def main(config_file):
	config = parse_config(config_file)

	top_dir = os.path.dirname(config_file)

	for root, dirs, files in os.walk(top_dir):
		if "raw" in dirs:  # indicates that the current directory contains a directory of raw frames

			# 1. adjust imu logfile
			adjust_imu_logfile_wrapper(root, config)

			#2. rescale with horizon painted on
			rescale_wrapper(root, 'temp', config, paint_horizon=True)

			# 3. make video
			make_video_wrapper(root, config)

			# 4. batch delete
			rmtree( os.path.join(root, 'temp') )

			# 5. rescale again, without horizon
			rescale_wrapper(root, 'rescaled_' + config.rescaling_desc, config)


if __name__ == "__main__":
	config_file = sys.argv[1]

	main(config_file)