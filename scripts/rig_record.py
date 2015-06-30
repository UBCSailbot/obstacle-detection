import subprocess as sp
import os
import signal

from support import mkdir_graceful

# Pathing configuration
bin_dir = "build"
bin_name = "rigRunner"

def start(repo_dir, output_dir):
  mkdir_graceful( os.path.join(output_dir, 'raw') )
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
