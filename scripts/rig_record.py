import subprocess as sp
import os
import signal


# Pathing configuration
bin_dir = "build"
bin_name = "rigRunner"

def make_dir_graceful(dir_name):
  if not os.path.exists(dir_name):
    os.makedirs(dir_name)

def start(repo_dir, output_dir):
  make_dir_graceful(output_dir)
  make_dir_graceful(os.path.join(output_dir, 'raw'))
  if not os.path.exists(output_dir):
    os.makedirs(output_dir)
  rig_record = sp.Popen(os.path.join(repo_dir, \
                                     bin_dir, \
                                     bin_name) + \
                        " " + output_dir, shell=True)
  return rig_record


def stop(process):
  try:
    pid = sp.check_output(["pidof", bin_name])
    os.kill(int(pid), signal.SIGHUP)
    os.system("pkill " + bin_name)
  except Exception:
    pass


def convert_to_video(top_dir, raw_dir):
  temp_dir = top_dir + "/tmp"
  os.mkdir(temp_dir)
  num_files = len(os.listdir(raw_dir))
  os.system(exec_dir + "/16to8/build/16to8 " + raw_dir + " " + temp_dir + " " + str(num_files))
  print exec_dir + "/16to8/build/16to8 " + raw_dir + " " + temp_dir + " " + str(num_files)
  os.system("ffmpeg -i \"" + temp_dir + "/img_%06d.png\" -r 24 -vf \"transpose=2\"" + top_dir + "/out.avi")
  rmtree(temp_dir)
