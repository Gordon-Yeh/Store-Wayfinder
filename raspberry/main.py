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
        
#        print(type(req))
#        print("req: "+req)
        query_type = req.split(",")[0]
        if (query_type == "n"):
            kw = req.split(",")[1]
            item_x, item_y = db.search_name(kw)
            pos_x, pos_y = cam.snapshot()
#           print(pos_x)
            ser.port.write(str.encode(str(item_x)+","+str(item_y)+","+str(pos_x)+","+str(pos_y)+"asdfghjkl"))
        if (query_type == "c"):
            kw = req.split(",")[1]
            names = db.search_cat(kw)
            for name in names:
                print(name[0])
                ser.port.write(name[0].encode())
        """
        if (req != "" and req!="\n"):

            #TODO: take and process picture
            print(req)
            query_type = req.split(",")[0]
            kw = req.split(",")[1]
            if (query_type == "n"):
                item_x, item_y = db.search_name(kw)
                pos_x, pos_y = cam.snapshot()
#                print(pos_x)
                ser.port.write(str.encode(str(item_x)+","+str(item_y)+","+str(pos_x)+","+str(pos_y)+"asdfghjkl"))
            if (query_type == "c"):
                names = db.search_cat(kw)
                for name in names:
                    print(name[0])
                    ser.port.write(name[0].encode())
            """
if __name__ == "__main__":
    main()