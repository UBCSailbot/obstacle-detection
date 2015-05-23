# On the raspberry pi, this script should be started from /etc/xdg/lxsession/LXDE-pi/autostart

import RPi.GPIO as GPIO
import time
import os
import rig_record as rig
import make_video as vid


# GPIO configuration
button_pin = 18
LED_pin = 21

GPIO.setmode(GPIO.BCM)
#GPIO.setup(button_pin, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(button_pin, GPIO.IN)
GPIO.setup(LED_pin, GPIO.OUT)

# path configuration
repo_dir = "/home/pi/obstacle_avoidance"
data_dir = "/home/pi/data"
current_dir = ""


# Control loop
recording = False
current_proc = 0

while True:
    button_pressed = GPIO.input(button_pin)

    if button_pressed:

        if not recording:
          recording = True
          GPIO.output(LED_pin, True)
          print "Now recording!"
          current_dir = os.path.join(data_dir, time.strftime("%d%H%M%S") )
          current_proc = rig.start(repo_dir, current_dir)
          time.sleep(1)

        else:
          recording = False
          GPIO.output(LED_pin, False)
          rig.stop(current_proc)
          print "Stopped recording."
          vid.convert_to_video(repo_dir, current_dir, os.path.join(current_dir, 'raw'))
          time.sleep(1)

