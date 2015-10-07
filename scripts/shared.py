import os


# Shared global constants
repo_dir = "/home/paul/sailbot/code/obstacle-avoidance"

data_dir = "/home/pi/data"

bin_dir = "build" 

default_imu_output_file = "imuLog.txt"
default_imu_output_file_adjusted = "imuLog_adjusted.txt"


# Accessory functions

def mkdir_graceful(dir_name):
  if not os.path.exists(dir_name):
    os.makedirs(dir_name)

def conditonal_concat(base, concat):
	if not concat in base:
		return base + concat
	return base_
