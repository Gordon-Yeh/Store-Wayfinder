#from serial import *
from pi_mysql import DB
from serial_comm import S
import time
from color import Camera

def main():
    ser = S()
    db = DB()
    cam = Camera()

    # TODO: format of input data
    while 1:
        req = ser.port.readline().decode("utf-8")

        query_type = req.split(",")[0]
        if (query_type == "p"):
            kw = req.split(",")[1]
            #item_x, item_y = db.search_name(kw)
            pos_x, pos_y = cam.snapshot()
            ser.port.write(str(pos_x)+","+str(pos_y)+"@@")

        # "c" indicating it's a valid user input requesting name and coordingantes in a certain category
        if (query_type == "c"):
            kw = req.split(",")[1]
            entries = db.search(kw)
            for entry in entries:
                print(entry[0])
                name = entry[0].encode()
                x = str(entry[1]).encode()
                y = str(entry[2]).encode()
                ser.port.write(name+"<"+x+">"+y+",")
            ser.port.write("?")
            
if __name__ == "__main__":
    main()