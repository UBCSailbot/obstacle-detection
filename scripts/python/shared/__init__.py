import os


# Shared global constants
repo_name = "obstacle-avoidance"

if not repo_name in os.path.abspath(__file__):
  raise Exception("The name of the repository to which this file belongs, \"{0}\", is not in this file's absolute path, which is {1}. This script relies on having the correct path for the parent source code repository.".format(repo_name, os.path.abspath(__file__)))

repo_dir = os.path.join(os.path.abspath(__file__).split(repo_name)[0], repo_name)

bin_dir = "build" 

default_imu_output_file = "imuLog.txt"
default_imu_output_file_adjusted = "imuLog_adjusted.txt"


# Accessory functions

def mkdir_graceful(dir_name):
  if not os.path.exists(dir_name):
    os.makedirs(dir_name)

def conditional_concat(base, concat):
	if not concat in base:
		return base + concat
	return base
