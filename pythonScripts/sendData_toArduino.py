
import time
import serial 

# open the serial communication
ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1.0)

# wait for sometime
time.sleep(3)

# read write from buffer
ser.reset_input_buffer()

print("Serial OK")

try:
    while True:
         ser.write("hi from raspi \n".encode('utf-8'))
         print("msg sent")

except KeyboardInterrupt:
    print("connection closed safely")
    # close the communication
    ser.close()
