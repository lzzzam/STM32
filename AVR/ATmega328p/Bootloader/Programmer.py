import sys
import serial
import progressbar
from intelhex import IntelHex

file = sys.argv[1]
port = sys.argv[2]
baud = sys.argv[3]

sign = "ZMBT"

print '---------- ', sign,' PROGRAMMER ------------'

#print Input info
print sign, ": File = ", file
print sign, ": Serial Port = ", port
print sign, ": Baudrate = ", baud

#open serial connection
try:
    serial = serial.Serial(port, baud, timeout=3)
except:
    print sign, ": Error: can't open serial port ", port
    sys.exit()

#read hex file
ih = IntelHex()
try:
    ih.loadhex(file)
except:
    print sign, ": Error: can't open file ", file
    serial.close()
    sys.exit()

#number of byte in a Flash page
ATmega328P_pagesize = 128
#number of bytes in hex file
nbytes = len(ih.addresses())
#nbytes rounded to multiple of page size
nbyte_pageAligned = (nbytes & 0xFFFFFF80) + ATmega328P_pagesize
# #start\end addresses
start_address = ih.minaddr()
end_address = start_address + nbyte_pageAligned-1

#print informations
print sign, ': Loading file App.hex'
print sign, ': min addr =', ih.minaddr(), 'max addr = ', ih.maxaddr()
print sign, ': memory segments= ', ih.segments()
print sign, ': nbytes = ', nbytes
print sign, ': nbyte rounded to Flash page = ', nbyte_pageAligned
print sign, ': start address = ', start_address, 'end address = ' , end_address
print ''


print sign, ': Start firmware update'
#send size
print sign, ": send Image Size..."
serial.write('S')
packet = bytearray()
packet.append((nbyte_pageAligned >> 8) & 0xFF)
packet.append(nbyte_pageAligned & 0xFF)
serial.write(packet)


#send starting address
print sign, ": Send Start Address..."
serial.write('A')
packet = bytearray()
packet.append((start_address >> 8) & 0xFF)
packet.append(start_address & 0xFF)
serial.write(packet)

#program uC
print sign, ": Programming..."

flash_address = start_address

bar = progressbar.ProgressBar(maxval=nbyte_pageAligned, \
    widgets=['Writing: ', progressbar.Bar('#','[', ']'), ' ', progressbar.Percentage(), '-', progressbar.FileTransferSpeed(),])

bar.start()
buff = ih.tobinarray(start_address, end_address)

#send Program command
serial.write('P')

for i in range(0,nbyte_pageAligned, ATmega328P_pagesize):

    for j in range(0, ATmega328P_pagesize):
        #increment address counter
        flash_address = flash_address + 1
        #transmit new byte
        tx = chr(buff[i+j])
        serial.write(tx)

        #read echo from bootloader
        rx = serial.read(1)
        #if timeout expired, signal error and close
        if(len(rx) == 0):
            print ''
            print sign, ': Error! Cant communicate with target device'
            print sign, ': Serial Programmer closing'
            serial.close()
            sys.exit()

        #convert to int
        rx = int(rx.encode('hex'), 16)

        #if transmitted value is not equal to received
        #signal error and close
        if(rx != buff[i+j]):
            print ''
            print sign, ': Error at address ', hex(flash_address),' --> ', hex(int(buff[i+j])), ' != ', hex(rx)
            print sign, ': Serial Programmer closing'
            print ''
            sys.exit()
            serial.close()
        else:
            bar.update(i+j)

bar.finish()


#verify stored firmware
bar = progressbar.ProgressBar(maxval=nbyte_pageAligned, \
    widgets=['Reading: ', progressbar.Bar('#','[', ']'), ' ', progressbar.Percentage(), '-', progressbar.FileTransferSpeed(),])

bar.start()

#send Read command
serial.write('R')

for i in range(0,nbyte_pageAligned, ATmega328P_pagesize):

    for j in range(0, ATmega328P_pagesize):
        #read echo from bootloader
        rx = serial.read(1)
        #if timeout expired, signal error and close
        if(len(rx) == 0):
            print ''
            print sign, ': Error! Cant communicate with target device'
            print sign, ': Serial Programmer closing'
            serial.close()
            sys.exit()

        #convert to int
        rx = int(rx.encode('hex'), 16)

        #if transmitted value is not equal to received
        #signal error and close
        if(rx != buff[i+j]):
            print ''
            print sign, ': Error at address ', hex(flash_address),' --> ', hex(int(buff[i+j])), ' != ', hex(rx)
            print sign, ': Serial Programmer closing'
            print ''
            serial.close()
            sys.exit()

        bar.update(i+j)

bar.finish()



#quit Bootloader and jump to Application
print sign, ": Exit Bootloader and jump to App"
serial.write('Q')
serial.close()
print sign, ': Program stored correctly'

print ''
