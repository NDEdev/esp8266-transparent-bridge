import socket
port = 5550
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.bind(("192.168.1.41", port))
print "waiting on port:", port
while 1:
    data, addr = s.recvfrom(1024)
    print data
