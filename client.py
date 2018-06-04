#!/usr/bin/env python

import socket

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

client.connect(("127.0.0.1", 9999))

while True:

    msg = raw_input("Message to send >>")

    client.send(msg)

    if msg == "close":
        break

print "Bye Bye..."

client.close()
