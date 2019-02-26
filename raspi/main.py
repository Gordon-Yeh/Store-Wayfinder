#from serial import *
from pi_mysql import DB
from serial_comm import S
import time


def main():
    ser = S()
    db = DB()

    # TODO: format of input data
    while 1:
        req = ser.port.readline()
        if (req != ""):
            """parse data --> query db --> send back the result
                (here assuming req is the name of the item to search)
                sendback format: 
                    item_x,item_y,user_x,user_y \n
            """ 

            #TODO: take and process picture
            query_type = req.split(",")[0]
            kw = req.split(",")[1]
            print(req)
            print(kw)
            if (query_type == "n"):
                item_x, item_y = db.search_name(kw)
                ser.port.write(str.encode(str(item_x)+","+str(item_y)))
            if (query_type == "c"):
                names = db.search_cat(kw)
                for name in names:
                    print(name[0])
                    ser.port.write(name[0].encode())
            
if __name__ == "__main__":
    main()