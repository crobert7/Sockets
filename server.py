#!/usr/bin/env python

import socket

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server.bind(("",9999))

server.listen(1)

sc, addr = server.accept()

while True:

    receive = sc.recv(1024)

    if receive == "close":
        break

    print str(addr[0]) + " say ", receive

    sc.send(receive)


sc.close()
server.close()
