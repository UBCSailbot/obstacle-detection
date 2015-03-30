import serial # pyserial library
import time
import numpy as np

ACCEL = 'ACCEL'
GYRO = 'GYRO'
SMOOTHING_WINDOW = 10

gravity_vector = np.array([0,0,960])

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
        vals  = [float( d.replace(u'\x00', '') ) for d in data[1:]]
    except UnicodeEncodeError, ValueError: 
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


"""
The number of attempts indicates the number of lines read from the IMU.
Keep in mind that the device outputs accel/gyro data on alternating lines.
Thus, the number of attempts for one particular field is really half the
number of total line reads.
"""
def get_field(ser, field_name, max_reads=10):
    vals = []
    num_reads = 0
    while not vals:
        data = pull_from_serial(ser)
        num_reads += 1
        error = 0       
        if field_name in data[0]:  
            vals, error = parse_list(data)
        if error:
            vals = []
        if num_reads >= max_reads:
            raise IOError("Failed to obtain {0} data within {1} attempts."\
                .format(field_name, max_reads) )
    return np.array(vals), num_reads

def get_field_smooth(ser, field_name, max_reads=10, smoothing=SMOOTHING_WINDOW):
    array_of_vals = np.array([])
    for i in range(smoothing):
        array_of_vals.append()

def calibrate(vector, orig_vector):
    return vector - orig_vector

def test():
    ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)
    fails = 0

    # Read data from STM32F3discovery
    #while 1:
    for i in range(135):
        #time.sleep(0.05)
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

# In Windows, COM ports are called COM1-COM10
# In Linux, COM ports are called ttyS0-ttyS10
def main():
    ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)
    start_accel = np.array( get_field(ser, ACCEL) )
    start_gyro = np.array( get_field(ser, GYRO) )

    test()

if __name__ == "__main__":
    main()

