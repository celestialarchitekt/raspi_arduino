import serial
import time

connection_count = 0   # how many times we've tried to connect
ser = None

# keep trying until connected or 10 attempts
while True:
    try:
        if connection_count > 10:
            print("Tried 10 times, giving up.")
            exit(1)

        ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1.0)
        print("Connected to /dev/ttyACM0")
        break

    except serial.SerialException:
        connection_count += 1
        print(f"Attempt {connection_count}: could not connect, retrying...")
        time.sleep(1)

# reset the buffer
ser.reset_input_buffer()

def sendData():
    ser.write("Hi from Raspi\n".encode("utf-8"))

def receiveData():
    if ser.in_waiting > 0:
        line = ser.readline().decode("utf-8").strip()
        print("Received:", line)

try:
    while True:
        ch = input("Enter 1 to send data, 2 to listen, q to quit: ").strip()

        if ch == "1":
            print("Sending data...")
            sendData()

        elif ch == "2":
            print("Listening for data (press Ctrl-C to stop)...")
            while True:
                receiveData()
                time.sleep(0.1)

        elif ch.lower() == "q":
            break

        else:
            print("Wrong choice, enter again (1 or 2)")

except KeyboardInterrupt:
    print("\nCtrl-C pressed, exiting")

finally:
    if ser:
        ser.close()
        print("Serial port closed.")

