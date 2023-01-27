import serial
import time
import os
from random import *
import datetime

## Starts the serial communication
# @param do_time Indicates whether time should be sent to Arduino
# @return The Serial address
# @warning Has a 2 second delay because the Serial port needs a small delay after opening communications.
def start_serial(do_time = True):
    path = ""
    for i in range(5):
        if os.path.exists('/dev/ttyACM' + str(i)):
            path = '/dev/ttyACM' + str(i)
            break
    #print("Started serial communication")
    ser = serial.Serial(path, 9600, timeout=1)
    time.sleep(2)
    if do_time:
        set_time(ser)
    return ser

## Stop the serial communication
# @param ser Serial
def stop_serial(ser):
    ser.close()
    #print("Stopped serial communication")

## Writes to serial buffer
# @param ser Serial
# @param message Message to send
def write(ser, message):
    message = bytes(message, encoding='utf8')
    ser.write(message)
    
## Writes to serial buffer expecting a response
# @param ser Serial
# @param message Message to send
# @return The response
def request(ser, message):
    ser.reset_input_buffer()
    write(ser, message)
    return ser.readline().decode('utf-8').rstrip()

## Gets the current operation mode
# @param ser Serial
# @param separate If True, mode 0 is humidity control, mode 1 is pre-scheduled daily and mode 2 is pre-scheduled weekly. If False (default), both pre-scheduled modes are returned as 1.
# @return Mode: 0 for Humidity control, 1 for Pre-scheduled
def get_mode(ser, separate = False):
    res = int(request(ser, "m\n"))
    if (not separate) and res == 2:
        res = 1
    return res

## Gets the time stored in the Arduino
# @param ser Serial
# @return Arduino time: days elapsed, weekday, hours, minutes, seconds
def get_time(ser):
    val = request(ser, "t\n")
    #print("Current time (Day, weekday, hour, minute, second): ", val)
    return val.split(",")
    
## Configures the time stored in the Arduino
# @param ser Serial
# @return True
def set_time(ser):
    now = datetime.datetime.now()
    out = now.strftime("T,%w,%-H,%-M,%-S\n")
    write(ser, out)
    return True

## Gets the current water source
# @param ser Serial
# @return Source: 0 for water tank, 1 for well pump
def get_source(ser):
    val = request(ser, "s\n")
    #print("Source:", val)
    return int(val)

## Sets the current water source
# @param ser Serial
# @param src Source to set
# @return True if source set correctly, False otherwise
def set_source(ser, src):
    current = request(ser, "s\n")
    if int(current) != src:
        out = "S,{:d}\n".format(src)
        write(ser, out)
        #print("Sent source:", out.replace("\n",""))
        current = request(ser, "s\n")
        if int(current) != src:
            return False
    return True

## Gets the current humidity
# @param ser Serial
# @param all If True, the function returns both current humidity and the set humidity parameters. If False (default), it only returns the current Humidity.
# @return Humidity, as a percentage (see all parameter)
# @warning This will only work properly if the sensor is connected to the 5V, otherwise 100% humidity is not 1023
def get_humidity(ser, all = False):
    val = request(ser, "h\n")
    #print("Humidity, minH, maxH: ", val)
    if not all:
        return int(val.split(",")[0]) / 1023
    if val.split(",")[1] == "-1" or val.split(",")[2] == "-1":
        return int(val.split(",")[0]) / 1023, None, None
    return int(val.split(",")[0]) / 1023, int(val.split(",")[1]) / 1023, int(val.split(",")[2]) / 1023

## Sets the Arduino to Humidity control mode as well as the parameters necessary
# @param ser Serial
# @param minH Minimum humidity (0 - 1023)
# @param maxH Maximum humidity (0 - 1023)
# @returns True if the parameters were set correctly and False otherwise
def set_humidity(ser, minH, maxH):
    out = "H,{:d},{:d}\n".format(minH, maxH)
    write(ser, out)
    #print("Sent humidity:", out.replace("\n",""))
    val = request(ser, "h\n").split(",")
    if (minH == int(val[1]) and maxH == int(val[2])):
        return True
    return False

## Gets the parameters in use for both of the Pre-scheduled modes
# @param ser Serial
# @returns (1, interval in days, list of time blocks) for Daily mode, (2, list of booleans where the days selected are True, list of time blocks) for Weekly mode, None for other modes
def get_prescheduled(ser):
    mode = get_mode(ser, True)
    if mode == 1:
        # Daily mode
        reply = request(ser, "d\n")
        #print("Reply:", reply)
        reply = reply.split(",")
        times = []
        for i in range(1, len(reply)):
            time_entries = reply[i].split(";")
            times.append([int(time_entries[0]), int(time_entries[1]), int(time_entries[2]), int(time_entries[3])])
        return 1, int(reply[0]), times
    elif mode == 2:
        # Weekly mode
        reply = request(ser, "w\n")
        #print("Reply:", reply)
        reply = reply.split(",")
        days = reply[0].split(";")
        days_list = [False, False, False, False, False, False, False]
        for i in days:
            days_list[int(i)-1] = True
        times = []
        for i in range(1, len(reply)):
            time_entries = reply[i].split(";")
            times.append([int(time_entries[0]), int(time_entries[1]), int(time_entries[2]), int(time_entries[3])])
        return 2, days_list, times
    else:
        return None, None, None

## Sets the Arduino to Pre-scheduled - Weekly mode as well as the parameters necessary
# @param ser Serial
# @param days A seven member list containing which days are to be included
# @param times List of the run times
# @return Whether the process was successful
def set_weekly(ser, days, times):
    out = "W,"
    day_string = ""
    for i in days:
        day_string += str(i) + ";"
    day_string = day_string[:-1]
    out += day_string + "," + str(len(times)) + ","
    times_string = ""
    for i in times:
        times_string += f"{int(i[0])};{int(i[1])};{int(i[2])};{int(i[3])},"
    times_string = times_string[:-1]
    out += times_string + "\n"
    write(ser, out)
    #print("Set weekly (W, days of the week, nr selected times, selected times):", out.replace("\n",""))
    reply = int(request(ser, "m\n"))
    if reply != 2:
        #print("Incorrect mode set!")
        return False
    reply = request(ser, "w\n")
    #print(reply)
    if (reply.split(",")[0] != day_string or reply[reply.find(",")+1:] != times_string):
        #print("Days and/or times incorrectly set")
        return False
    return True

## Sets the Arduino to Pre-scheduled - Daily mode as well as the parameters necessary
# @param ser Serial
# @param days Day interval (1 for every day, 2 for every other day, etc)
# @param times List of the run times
# @return Whether the process was successful
def set_daily(ser, interval, times):
    out = f"D,{int(interval)},"
    out += str(len(times)) + ","
    times_string = ""
    for i in times:
        times_string += f"{int(i[0])};{int(i[1])};{int(i[2])};{int(i[3])},"
    times_string = times_string[:-1]
    out += times_string + "\n"
    write(ser, out)
    #print("Set daily (D, interval, nr selected times, selected times):", out.replace("\n",""))
    reply = int(request(ser, "m\n"))
    if reply != 1:
        #print("Incorrect mode set!")
        return False
    reply = request(ser, "d\n")
    #print(reply)
    if (int(reply.split(",")[0]) != interval or reply[reply.find(",")+1:] != times_string):
        #print("Days and/or times incorrectly set")
        return False
    return True