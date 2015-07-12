import os


# Shared global constants
repo_dir = "/home/pi/obstacle_avoidance"

data_dir = "/home/pi/data"

bin_dir = "build" 


# Accessory functions

def mkdir_graceful(dir_name):
  if not os.path.exists(dir_name):
    os.makedirs(dir_name)
