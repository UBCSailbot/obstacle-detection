import RPi.GPIO as GPIO
import time
import os
import rig_record as rig


# GPIO configuration
button_pin = 18
LED_pin = 21

GPIO.setmode(GPIO.BCM)
#GPIO.setup(button_pin, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(button_pin, GPIO.IN)
GPIO.setup(LED_pin, GPIO.OUT)

# path configuration
repo_dir = "/home/pi/obstacle-avoidance"
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
          print "Now recording!"
          current_dir = os.path.join(data_dir, time.strftime("%d%H%M%S") )
          current_proc = rig.start(repo_dir, os.path.join(current_dir))
          time.sleep(1)

        else:
          recording = False
          rig.stop(current_proc)
          print "Stopped recording."
          time.sleep(1)

