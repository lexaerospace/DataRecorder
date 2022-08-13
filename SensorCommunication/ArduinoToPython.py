#imports pyserial package (in terminal to install package type 'pip install pyserial')
import serial

#gets ardunio serial data
serialData = serial.Serial("COM3", 9600)

#loops infinitely
while True:
    if serialData.inWaiting() > 0:
        #takes the data from SensorCommunication.ino and converts it from byte to string
        data = serialData.readline().decode('utf-8')
        #prints data
        print(data, end='')
