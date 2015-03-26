import serial # pyserial library

# Reads a line of data from the STM32F3discovery board
# Returns the accelerometer and gyroscope data as a list tuple (accel, gyro)

def read_data():

    # Flush any old data from serial port
    ser.flush() 
    
    # These lists will hold the accel and gyro data
    gyro  = []
    accel = []

    # Read a line from the serial port and split it at every instance of a tab character
    
    data = ser.readline().decode("utf-8")
    data = data.split('\t')
    print data

    # Check what type of data was received and save it to the proper list

    if   data[0] == "GYRO":  gyro  = [float(d) for d in data[1:]]
    elif data[0] == "ACCEL": accel = [float(d) for d in data[1:]]
    else: raise Exception("Unknown data received. Expected GYRO or ACCEL, but got: " + ''.join(data) )


    # In the previous read, we either received GYRO or ACCEL data
    # Now we read another line to get the other data
    # Check what type of data was received and save it to the proper list

    if   data[0] == "GYRO":  gyro  = [float(d) for d in data[1:]]
    elif data[0] == "ACCEL": accel = [float(d) for d in data[1:]]
    else: raise Exception("Unknown data received. Expected GYRO or ACCEL, but got: " + ''.join(data) )


    # Make sure that both the accelerometer and gyroscope data was obtained
    if len(gyro) == 0 or len(accel) == 0:
        raise Exception("Unkown error occurred. Unable to read both GYRO and ACCEL data.")
    
    return (accel, gyro)



# In Windows, COM ports are called COM1-COM10
# In Linux, COM ports are called ttyS0-ttyS10

ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)


# Read data from STM32F3discovery

accel_data, gyro_data = read_data()

# Close the serial port when done
ser.close() 



