import time
import serial
import math

# configure the serial connections (the parameters differs on the device you are connecting to)
ser = serial.Serial(
    port='/dev/ttyUSB0',
    baudrate=57600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS
)
#define Serial Commands
PID = '(500,1000,10000,100,0,0,100\r'

MOTOR = 'Q'
MOTORSPEED = '0'
MOTORPARAMS = ',0,0,2800,5000,5000,5000,2000,1000,50,1\r'

RESET = 'R\r'

while 1:

    ser.isOpen()
    print('Enter to continue, exit to close')
    decision = input('>>')

    if decision == ('exit'):
            ser.close()
            exit(0)

    else:
    
        RPM = int(input('Enter Speed in RPM 500--4500 \n>>'))
        var = float(RPM*8.333)
        var = int(var)

        MOTORSPEED = str(int(var))

        #print(MOTORSPEED)
        #print(PID)
        #print(MOTOR)
        #print(RESET)

        MOTOR = MOTOR+MOTORSPEED+MOTORPARAMS
        #print(MOTOR)
        MOTORENCODED = str.encode(MOTOR)

        ser.write(b'R\r')
        ser.write(b'(500,1000,10000,100,0,0,100\r')

        print('PID command Sent')
        time.sleep(2)
        
        print('starting motor')
        ser.write(MOTORENCODED)
        print('Motor Command Sent')

        print('Run for 15 seconds')
        time.sleep(15)
                
        ser.write(b'H2222,0,1000,1000,500,50,1\r')
        print('Slowing Motor')
        

        time.sleep(8)
        print('Stopping Motor\n\n')
        ser.write(b'R\r')


        

