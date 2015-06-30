import os

def mkdir_graceful(dir_name):
  if not os.path.exists(dir_name):
    os.makedirs(dir_name)
