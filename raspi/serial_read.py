import time
import serial

counter = 0
    
def serial_init():
    ser = serial.Serial(
        port = '/dev/serial0',
        baudrate = 115200,
        parity = serial.PARITY_NONE,
        stopbits = serial.STOPBITS_ONE,
        bytesize = serial.EIGHTBITS,
        timeout = 1
    )
    return ser

def main():
    ser = serial_init()
    while 1:
        req = ser.readline()
        if(req == ""):
            print("lol")
        else:
            print("else")
        time.sleep(1)
        
if __name__ == '__main__':
    main()
