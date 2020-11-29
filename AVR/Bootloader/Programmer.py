import sys
import serial
import progressbar
from intelhex import IntelHex

file = sys.argv[1]
port = sys.argv[2]
baud = sys.argv[3]

print '---------- WASP PROGRAMMER ------------'

#print Input info
print "WP: File = ", file
print "WP: Serial Port = ", port
print "WP: Baudrate = ", baud

#open serial connection
try:
    serial = serial.Serial(port, baud, timeout=None)
except:
    print "WP: Error: can't open serial device ", port
    sys.exit()

#read hex file
ih = IntelHex()
ih.loadhex('file')#('WaspBoot.hex')

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
print 'WP: Loading file App.hex'
print 'WP: min addr =', ih.minaddr(), 'max addr = ', ih.maxaddr()
print 'WP: memory segments= ', ih.segments()
print 'WP: nbytes = ', nbytes
print 'WP: nbyte rounded to Flash page = ', nbyte_pageAligned
print 'WP: start address = ', start_address, 'end address = ' , end_address
print ''


print 'WP: Start firmware update'
#send size
print "WP: send Image Size..."
serial.write('S')
packet = bytearray()
packet.append((nbyte_pageAligned >> 8) & 0xFF)
packet.append(nbyte_pageAligned & 0xFF)
serial.write(packet)


#send starting address
print "WP: Send Start Address..."
serial.write('A')
packet = bytearray()
packet.append((start_address >> 8) & 0xFF)
packet.append(start_address & 0xFF)
serial.write(packet)

#program uC
print "WP: Programming..."
bar = progressbar.ProgressBar(maxval=nbyte_pageAligned, \
    widgets=[progressbar.Bar('#','[', ']'), ' ', progressbar.Percentage(), '-', progressbar.FileTransferSpeed(),])

bar.start()
buff = ih.tobinarray(start_address, end_address)
serial.write('P')
for i in range(0,nbyte_pageAligned, ATmega328P_pagesize):
    for j in range(0, ATmega328P_pagesize):
        tx = chr(buff[i+j])
        serial.write(tx)
        rx = int(serial.read().encode('hex'), 16)
        if(rx != buff[i+j]):
            print "Error"
            break
        bar.update(i+j)

bar.finish()
print ''

#quit Bootloader and jump to Application
print "WP: Exit Bootloader and jump to App"
serial.write('Q')
serial.close()
