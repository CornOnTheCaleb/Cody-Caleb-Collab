#!/usr/bin/python3

# This python script controls an HTTP webserver with TCP sockets

# Networking Terminology
# - IP: Internet Protocol (Network Layer)
# - TCP: Transmission Control Protocol (Transport Layer) (connections)
# - UDP: User Datagram Protocol (Transport Layer) (connectionless)
# - HTTP: Hypertext Transfer Protocol (Application Layer)
# - Socket: Endpoint of a connection defined by:
#     1. an IP address
#     2. a transport protocol (TCP or UDP)
#     3. a port
# - Port: A number (1-65535) that signifies logical gate in a device

import socket # Module used for sockets (obviously!)
import sys # Really only imported for sys.exit() (for some reason...)
import subprocess # Used for running other processes during script

# Create TCP server socket
# - socket.AF_INET used for IPv4 protocols
# - socket.SOCK_STREAM used for TCP
# - socket.SOCK_DGRAM used for UDP
serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Set a socket option to allow process to bind to port in TIME_WAIT
# - socket.SOL_SOCKET means the socket layer itself
# - socket.SO_REUSEADDR is the option to forcibly bind to a socket
serverSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

# Get IP address of wlan0 using ifconfig subprocess (might not be best way)
# - subprocess.check_output() returns output from shell command
# - socket.gethostbyname() returns corresponding value in /etc/hosts
# - socket.gethostname() returns contents of /etc/hostname
tmp = str(subprocess.check_output(['ifconfig']))
serverHost = tmp[tmp.find("inet", tmp.find("wlan0")) + 5: tmp.find(" ", tmp.find("inet", tmp.find("wlan0")) + 5)]

# Assign port number (port 80 it typically used for HTTP servers)
serverPort = 80

# Bind the socket to host IP address and port
serverSocket.bind((serverHost, serverPort))

# Set up TCP listener with a maximum number of connections at a time
serverMaxConnections = 1
serverSocket.listen(serverMaxConnections)

# Control loop of the webserver
# Accept a connection and process data received (hopefully HTTP requests)
# Stop the server with by pressing Ctrl+C
print("Server (" + serverHost + ":" + str(serverPort) + ") is ready for duty!")
serverShouldTerminate = False
while not serverShouldTerminate:
  try:
    # Wait for someone to form a connection
    # - <socket>.accept() does not return until a connection arrives
    connectionSocket, clientAddress = serverSocket.accept()
    print(" > Established connection with: " + str(clientAddress))

    # Receive data from the client
    # - <socket>.recv() receives a TCP message ("segment")
    # - <socket>.send() transmits a TCP message ("segment")
    # - <socket>.recvfrom() receives a UDP message ("datagram")
    # - <socket>.sendto() transmits a UDP message ("datagram")
    maxBytesToReceive = 2048
    messageReceived = connectionSocket.recv(maxBytesToReceive).decode()
    print("   - Received " + str(len(messageReceived)) + " bytes of data")

    # Send data back to the client (contents of file is exists)
    try:
      # Gets filename from HTTP header and removes the slash
      filename = messageReceived.split()[1][1:]

      print(" > Requested file: " + filename)
      
      # If no file was specified, send index.html
      if len(filename) == 0:
        filename = "index.html"

      # Remove all ".." from filename so only files in current directory can be reached
      filename = "./src/" + filename.replace("../", "").replace("..", "")

      # Set content type depending on requested file
      contentType = ""
      if ".html" in filename or ".php" in filename:
        contentType = "text/html"
      elif ".css" in filename:
        contentType = "text/css"
      elif ".js" in filename:
        contentType = "application/javascript"
      elif ".png" in filename:
        contentType = "image/png"
      else:
        contentType = "text/plain"

      # Run PHP if you want to
      fileContents = ""
      if ".php" in filename:
        fileContents = subprocess.check_output(["php", "-f", filename])
      else:
        # Open and read the file's contents (will fail if doesn't exist)
        if "image" in contentType:
          fileToRead = open(filename, "rb")
          fileContents = fileToRead.read()
          fileToRead.close()
        else:
          fileToRead = open(filename, "r")
          fileContents = fileToRead.read() + "\r\n"
          fileContents = fileContents.encode()
          fileToRead.close()

      # Send HTTP response header
      responseHeader = "HTTP/1.1 200 OK\r\nServer: Simple TCP Server\r\nConnection: close\r\nContent-Type: " + contentType + "\r\n\r\n"
      
      connectionSocket.sendall(responseHeader.encode())
      connectionSocket.sendall(fileContents)
    except IOError:
      try:
        # File requested doesn't exist so open threw an exception
        # Thus, the webserver will respond with 404 Not Found
        connectionSocket.sendall("HTTP/1.1 404 Not Found\r\n\r\n".encode())
        
        # Give the user something to look at
        connectionSocket.sendall("<html><head></head><body><h1>404 Not Found</h1></body></html>\r\n".encode())
      except:
        continue
    except:
      continue

    # Close the connection socket since the connection should be done
    connectionSocket.close()
  except KeyboardInterrupt:
    serverShouldTerminate = True

# Close the socket since the webserver is done
serverSocket.close()

# Terminate the program (is this call necessary?)
sys.exit()
