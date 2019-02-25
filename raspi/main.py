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
            item_x, item_y = db.search_name(req)
            ser.write(item_x+","+item_y)