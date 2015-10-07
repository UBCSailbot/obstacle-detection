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
import rescale_multiple
import shared

import sys

def parse_config(config_file):


def adjust_imu_logfiles(experiment_dir, config):
	adjust_imu_logfile.adjust_imu_logfiles(experiment_dir, config.roll_offset, config.pitch_offset, invert_roll=config.invert_roll, invert_pitch=config.invert_pitch)

def rescale_multiple(experiment_dir, config):
	rescale_multiple.rescale_multiple(experiment_dir, horizon_file_name=shared.default_imu_output_file_adjusted, options=shared.conditional_concat(config.rescaling_options, " --paint-horizon"), description=config.rescaling_desc)


def delete_temp_rescaled_frames(experiment_dir, config):
	for root, dirs, files in os.walk(experiment_dir):
		if config.rescaling_ in dirs:


def main(config_file):
	config = parse_config(config_file)

	top_dir = os.path.dirname(config_file)

	# 1. adjust imu logfiles	
	adjust_imu_logfiles(top_dir, config)

	#2. rescale with horizon painted on & 3. make videos
	rescale_multiple(top_dir, config)

	# 4. batch delete
	delete_temp_rescaled_frames(top_dir, config)

	# 5. batch rescale again, without horizon



	for capture_dir in [os.path.join(top_dir, x) for x in os.listdir(top_dir) if os.path.isdir(x)]:
		
		new_imu_logfile = adjust_imu_logfile(capture_dir, config)

		raw_dir = os.path.join(top_dir, capture_dir)
		rescaled_dir = 






if __name__ == "__main__":
	config_file = sys.argv[2]

	main(config_file)