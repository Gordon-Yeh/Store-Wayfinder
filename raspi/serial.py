"""
Read json format user request from the serial port then query
    the database according to the request type. Return the result
    via the same serial port. 

Expects requests to include fields below seperated by coma:
    search_type: "n"/"c",
    keyword: the keyword to search for

"""
import time
import serial
import json 
import pi_mysql as mysql

    
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

# def mainSerial():
#     ser = serial_init()
#     cursor = mysql.db_init()
#     while 1:
#         data = ser.readline()
#         if(data != ""):
#             req = json.load(data)
#             kw = req["kw"]
#             if (req["t"] == "n"):
#                 result = mysql.search_name(cursor, kw) #return the coordinate
#             else:
#                 result = mysql.search_cat(cursor,kw)
#             time.sleep(0.5)
#             ser.write(result)



        
