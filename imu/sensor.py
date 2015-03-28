import serial # pyserial library
import time

# Reads a line of data from the STM32F3discovery board
# Returns the accelerometer and gyroscope data as a list tuple (accel, gyro)

"""
Read a line from the serial port and split it at every instance of a tab character
"""
def pull_from_serial(ser_connection):
    ser_connection.flush() 
    data = ser_connection.readline().decode("utf-8")
    data = data.split('\t')
    return data


def parse_list(data):
    vals = []
    fail_count = 0
    try: 
        vals  = [float(d) for d in data[1:]]
    except UnicodeEncodeError: 
        print "Failed read: " + str(data)
        fail_count += 1
    return vals, fail_count


def read_data(ser, failed_reads):
    gyro  = []
    accel = []
    fc = 0

    # Read next 2 lines from serial.
    for i in range(2):
        data = pull_from_serial(ser)
        
        # Check what type of data was received, and save it to the proper list
        if   'GYRO' in data[0]:  
            gyro, fc = parse_list(data)
        elif 'ACCEL' in data[0]:
            accel, fc = parse_list(data)
        else: 
            raise AttributeError("Unknown data received. Expected GYRO or ACCEL, but got: " + str(data) )

    failed_reads += fc
    
    # Make sure that both the accel and gyro data were obtained
    if len(gyro) == 0 and len(accel) == 0:
        print data
        raise IOError("Unkown error occurred. Unable to read both GYRO and ACCEL data.")
    
    return (accel, gyro, failed_reads)


# In Windows, COM ports are called COM1-COM10
# In Linux, COM ports are called ttyS0-ttyS10
def main():
    ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)
    fails = 0

    # Read data from STM32F3discovery
    while 1:
        time.sleep(0.05)
        try:
            accel_data, gyro_data, fails = read_data(ser, fails)
            print "Accel: " + '  '.join(['{:8.3f}'.format(val) for val in accel_data]) + \
               "   Gyro: "  + '  '.join(['{:8.3f}'.format(val) for val in gyro_data])
        except AttributeError as ae:
            print ae
            fails += 1
            print "Failed reads: " + str(fails)

    #print read_data()

    # Close the serial port when done
    ser.close() 

if __name__ == "__main__":
    main()

