"""
+-----------------------+
| IMU log file adjuster |
+-----------------------+

Frequently, for whatever reason, when we gather data out in the real world, our IMU is not calibrated quite right, or at least one of its axes is inverted relative to what we'd expect. 

When our boat ("Ada") is ready to cross the Atlantic, we can be reasonably confident that the last-minute constraints of preparing for a 1-day field test will not be present, and so we will have had the time to properly calibrate the on-board IMU.

Therefore, for now, we've decided that the best practice is to:
  1) Manually determine what adjustments need to be made to the IMU (these should be the same for an entire recording session)
  2) Go back and regenerate IMU output files with these adjustments made (though making sure to keep the original output files)
  3) Re-run rescaling, or whatever other horizon-dependent pre-processing, with the adjusted IMU log file.

Of the steps listed above, this script takes care of #2.
"""

import __init__
import shared

def adjust_imu_logfile(logfile_path, roll_offset, pitch_offset, invert_roll=False, invert_pitch=False):

  new_text = []

  for line in open(logfile_path).readlines():
    roll, pitch, yaw = map(float, line.split())
    roll += roll_offset
    pitch += pitch_offset
    if invert_roll:
      roll *= -1
    if invert_pitch:
      pitch *= -1
    new_text.append(' '.join([str(roll), str(pitch), str(yaw)]) + '\n')

  dot_index = logfile_path.find('.')
  pre_ext = logfile_path[:dot_index]
  post_ext = logfile_path[dot_index + 1:]

  new_imu_logfile = pre_ext + "_adjusted." + post_ext

  open(new_imu_logfile, 'w').writelines(new_text)
  return new_imu_logfile

def batch_adjust_imu_logfiles(experiment_dir, roll_offset, pitch_offset, invert_roll=False, invert_pitch=False):

  import os

  for root, dirs, files in os.walk(experiment_dir):
    for f in files:
      if f == shared.default_imu_output_file:
        full_path = os.path.join(root, f)
        try:
          adjust_imu_logfile(full_path, roll_offset, pitch_offset, invert_roll, invert_pitch)
        except ValueError:
          print "WARNING: Failed to adjust file ", full_path


def print_usage():
  print "Usage: python {0} [-f <imu-logfile> | -d <experiment-dir>] <roll-offset> <pitch-offset> [--invert-roll --invert-pitch]".format(sys.argv[0])


if __name__ == "__main__":
  import sys
  import argparse

  min_num_args = 4
  max_num_args = 6

  if len(sys.argv) < min_num_args + 1 or len(sys.argv) > max_num_args + 1:
    print_usage()
    sys.exit()

  flag = sys.argv[1]
  logfile_path = sys.argv[2]
  roll_offset = float(sys.argv[3])
  pitch_offset = float(sys.argv[4])

  invert_roll = "--invert-roll" in sys.argv
  invert_pitch = "--invert-pitch" in sys.argv

  # if "--invert-roll" in sys.argv:
  #   invert_roll = True

  # if "--invert-pitch" in sys.argv:
  #   invert_pitch = True

  if flag == "-f":
    adjust_imu_logfile(logfile_path, roll_offset, pitch_offset, invert_roll, invert_pitch)

  elif flag == "-d":
    batch_adjust_imu_logfiles(logfile_path, roll_offset, pitch_offset, invert_roll, invert_pitch)

  else:
    print_usage()
    sys.exit()
