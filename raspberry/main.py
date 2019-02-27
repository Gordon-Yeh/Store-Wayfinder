#from serial import *
from pi_mysql import DB
from serial_comm import S
import time
from color import Camera

def main():
    ser = S()
    db = DB()
    cam = Camera()

    while 1:
        pos_x, pos_y = cam.snapshot()
        print(pos_y)
        time.sleep(1)
        req = ser.port.readline().decode("utf-8")
        query_type = req.split(",")[0]
        if (query_type == "p"):
            pos_x, pos_y = cam.snapshot()
            result = "@"+str(pos_x)+","+str(pos_y)+"?"
            ser.port.write(result.encode())

        # "c" indicating it's a valid user input requesting name and coordingantes in a certain category
        if (query_type == "c"):
            kw = req.split(",")[1]
            entries = db.search(kw)
            ser.port.write(str("@").encode())
            for entry in entries:
                print(entry[0])
                name = entry[0]
                x = str(entry[1])
                y = str(entry[2])
                msg = name+"<"+x+">"+y+","
                ser.port.write(msg.encode())
            ser.port.write(str("?").encode())
            
if __name__ == "__main__":
    main()