import subprocess as sp
import os
import signal
import shutil

import __init__
import shared
from image_proc.rescale import rescale
import video.make_video as vid

# Pathing configuration
bin_name = "rigRunner"

def start(repo_dir, output_dir):
  shared.mkdir_graceful( os.path.join(output_dir, 'raw') )
  rig_record = sp.Popen(os.path.join(repo_dir, \
                                     shared.bin_dir, \
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

def convert_to_video( frame_dir, imu_file ):
    parent_dir = os.path.dirname( frame_dir )
    tmp_dir = os.path.join(parent_dir, 'rescaled_tmp')
    rescale( frame_dir, tmp_dir, orientation_file=imu_file )
    video_file = os.path.join(parent_dir, 'out.avi')
    vid.convert_to_video(tmp_dir, video_file)
    shutil.rmtree(tmp_dir)

