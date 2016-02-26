# On the raspberry pi, this script should be started from /etc/xdg/lxsession/LXDE-pi/autostart

import RPi.GPIO as GPIO
import time
import os, sys

import __init__
import rig_record as rig
from shared import repo_dir


# GPIO configuration
record_pin = 18
off_pin = 16
LED_pin = 21

GPIO.setmode(GPIO.BCM)
#GPIO.setup(record_pin, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(record_pin, GPIO.IN)
GPIO.setup(off_pin, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(LED_pin, GPIO.OUT)


def record_data_to(data_dir):

    print "RigRunner started."

    recording = False
    current_proc = 0
    current_dir = ""
    shutdown_counter = 0

    while True:
        record_button_pressed = GPIO.input(record_pin)
        shutdown_button_pressed = not GPIO.input(off_pin)

        if record_button_pressed:

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
              rig.convert_to_video( os.path.join(current_dir, 'raw'), os.path.join(current_dir, 'imuLog.txt')  )
              time.sleep(5)

        if shutdown_button_pressed and not recording:
            shutdown_counter += 1
            time.sleep(0.1)
            if shutdown_counter == 50:
                print "System is going down for shutdown NOW!"
                os.system("sudo shutdown -h now")
                sys.exit()
        elif not shutdown_button_pressed:
            shutdown_counter = 0

def main():
    if len(sys.argv) < 2:
        print "Usage: {0} [output_dir]".format(sys.argv[0])
        sys.exit()

    data_dir = sys.argv[1]
    record_data_to(data_dir)

if __name__ == "__main__":
    main()
