#written by Junhyeok Jeong
#CS 372 - Lab1 extra credit
#Language: python 3.x

import socket
import sys
import http.client
import urllib

#create an INET and STREAM socket
try:
	sc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	print ("Socket Successfully created")
#error handling
except socket.error as err:
	print ("Socket creation failed with error {}".format(err))

#default port for socket
port = 80

#set host by internet address
try:
	host_ip = socket.gethostbyname('gaia.cs.umass.edu')
#error handling
except socket.gaierror:
	print ("there was an error resolving the host")
	sys.exit()

sc.connect((host_ip, port))

print ("the socket has successfully connected to gaia.cs.umass.edu: {}".format(host_ip))

connection = http.client.HTTPSConnection('gaia.cs.umass.edu')
connection.request("GET", "/")
response = connection.getresponse()
print ("connection status: {} and reason: {}".format(response.status, response.reason))

connection.close()

#references
#python documents site: docs.python.org/3/howto/sockets.html
#			docs.python.org/3/library/http.client.html

