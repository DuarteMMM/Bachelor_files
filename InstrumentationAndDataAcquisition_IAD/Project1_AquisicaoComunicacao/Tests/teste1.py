# 1o passo: ls /dev/tty*
# O nome do arduino vai aparecer, deve ser algo do tipo '/dev/ttyACM0'
# Substituir abaixo o nome correto!!

# Pode ser necessário fazer o seguinte: python3 -m pip install pyserial
# Se der erro, fazer o seguinte e depois repetir: sudo apt install python3-pip

#!/usr/bin/env python3
import serial
if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    ser.reset_input_buffer()
    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').rstrip()
            print(line)