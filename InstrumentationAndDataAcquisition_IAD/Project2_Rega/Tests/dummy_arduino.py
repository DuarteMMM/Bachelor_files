import time
import os
from random import *
import datetime

def start_serial(do_time = True):
    return 1

def write(ser, message):
    #message = bytes(message, encoding='utf8')
    #ser.write(message)
    print("Sent:" + message)
    
def request(ser, message):
    #ser.reset_input_buffer()
    #write(ser, message)
    #return ser.readline().decode('utf-8').rstrip()
    print("Requested: " + message)
    return -1

def get_mode(ser):
    request(ser, "m\n")
    return 1
    
def set_time(ser):
    now = datetime.datetime.now()
    out = now.strftime("T,%w,%-H,%-M,%-S\n")
    write(ser, out)
    return True

def get_time(ser):
    val = request(ser, "t\n")
    print(val)
    return val.split(",")

def stop_serial(ser):
    print("Stopped serial communication")

def get_source(ser):
    val = request(ser, "s\n")
    print("Fonte:", val)
    return 0

def set_source(ser, src):
    current = request(ser, "s\n")
    if int(current) != src:
        out = "S,{:d}\n".format(src)
        write(ser, out)
        print("Sent source:", out)
        current = request(ser, "s\n")
        if int(current) != src:
            return False
    return True

def get_humidity(ser):
    val = request(ser, "h\n")
    print(val)
    # Testing
    get_time(ser)
    return int(val.split(",")[0]) / 1023

def set_humidity(ser, minH, maxH):
    out = "H,{:d},{:d}\n".format(minH, maxH)
    write(ser, out)
    print("Sent humidity:", out)
    val = request(ser, "h\n").split(",")
    if (minH == int(val[1]) and maxH == int(val[2])):
        return True
    return False