import zmq
import time
import sys
import os
port = "5555"
if len(sys.argv) > 1:
    port =  sys.argv[1]
    int(port)

context = zmq.Context()
socket = context.socket(zmq.SUB)
os.system('read -s -n 1 -p "Press any key to continue..."')
socket.connect ("tcp://localhost:%s" % port)
socket.setsockopt_string(zmq.SUBSCRIBE, "")


while True:
    #  Wait for next request from client
    message = socket.recv()
    print ("Received request: ", message)
