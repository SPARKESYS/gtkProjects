import time
import serial



# configure the serial connections (the parameters differs on the device you are connecting to)
ser = serial.Serial(
    port='/dev/ttyUSB0',
    baudrate=57600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS
)

ser.isOpen()

print ('Enter your commands below.\r\nInsert "exit" to leave the application.')

inputVal=1
while 1 :
    # get keyboard input
    inputVal = input(">> ")
        # Python 3 users
        # input = input(">> ")
    if inputVal == 'exit':
        ser.close()
        exit()
    else:
        # send the character to the device
        ser.write(inputVal + '\r')
        out = ''
        # let's wait one second before reading output (let's give device time to answer)
        time.sleep(1)
        while ser.inWaiting() > 0:
            out += ser.read(1)

        if out != '':
            print (">>" + out)
