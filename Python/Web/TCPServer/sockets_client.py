#!/usr/bin/env python3

import socket

serverPort = 80
serverName = "10.106.78.138"
clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
clientSocket.connect((serverName, serverPort))
message = input("Input any message: ")
clientSocket.send(message.encode())
maxBytesToReceive = 8192
for i in range(10):
  message = clientSocket.recv(maxBytesToReceive)
  print("From Server: ", message.decode())
clientSocket.close()
