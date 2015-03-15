#!/usr/bin/python

# check if already running
import os, sys
if os.path.isfile("/home/pi/pylock"):
  sys.exit()

import RPi.GPIO as GPIO
import time
import subprocess
from shutil import rmtree

xserver = False

try:
  xserver = (os.environ['DISPLAY'] == ':0.0')
except KeyError:
  pass

# get root access
euid = os.geteuid()
if euid != 0:
  args = ['sudo', sys.executable] + sys.argv + [os.environ]
  # the next line replaces the currently-running process with the sudo
  os.execlpe('sudo', *args)

print "Now running with root access."
os.system("touch /home/pi/pylock")

GPIO.setmode(GPIO.BCM)

GPIO.setup(18, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(15, GPIO.OUT)
GPIO.output(15, False)
recording = False

exec_dir = "/home/pi/obstacle-avoidance/rpi_lepton_video"

out_dir = "/home/pi/lepton-out/"
current_dir = ""

def convert_to_video(top_dir, raw_dir):
  temp_dir = top_dir + "/tmp"
  os.mkdir(temp_dir)
  num_files = len(os.listdir(raw_dir))
  os.system(exec_dir + "/16to8/build/16to8 " + raw_dir + " " + temp_dir + " " + str(num_files))
  print exec_dir + "/16to8/build/16to8 " + raw_dir + " " + temp_dir + " " + str(num_files)
  os.system("ffmpeg -i \"" + temp_dir + "/img_%06d.png\" -r 24 -vf \"transpose=2\"" + top_dir + "/out.avi")
#  rmtree(temp_dir)

while True:
  input_state = GPIO.input(18)

  if input_state == False and not recording:
    GPIO.output(15, True)    
    current_dir = out_dir + time.strftime("%y%m%d%H%M%S");
    raw_dir = current_dir + "/raw"
    os.makedirs(raw_dir)
#    os.putenv('DISPLAY', ':0.0')
    lepton_video = subprocess.Popen(exec_dir + "/build/lepton_video " + raw_dir, shell=True)
    print [exec_dir + "/build/lepton_video", raw_dir]
    recording = True
    print "starting video"
    time.sleep(1.5)
    os.system("touch " + out_dir + "recording.txt")
  elif input_state == False and recording:
    GPIO.output(15, False)    
    print "killing process"
    try:
      pid = subprocess.check_output(["pidof", "lepton_video"])
      os.system("kill "+pid)
      convert_to_video(current_dir, raw_dir)
    except subprocess.CalledProcessError:
      pass
    finally:
      os.system("rm " + out_dir + "recording.txt")
    

    recording = False
    time.sleep(1.5)
