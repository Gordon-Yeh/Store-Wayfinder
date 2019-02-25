#from serial import *
from pi_mysql import *
from serial_comm import *
import time


def main():
    ser = serial_init()
    cursor = db_init()

    # TODO: format of input data
    while 1:
        req = ser.readline()
        if (req != ""):
            """parse data --> query db --> send back the result
                (here assuming req is the name of the item to search)
                sendback format: 
                    item_x,item_y,user_x,user_y \n
            """ 

            #TODO: take and process picture
            item_x, item_y = search_name(cursor, req)
            ser.write(item_x+","+item_y)


if __name__ == '__main__':
    main()