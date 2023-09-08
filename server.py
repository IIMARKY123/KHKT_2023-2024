# Python 3 server example
from http.server import BaseHTTPRequestHandler, HTTPServer
from PyAccessPoint import pyaccesspoint
import time
import requests

access_point = pyaccesspoint.AccessPoint()
#access_point.start()

hostName = "192.168.1.194"
serverPort = 80
a=3
b=43
c=10
d=13
e=19

val5 = requests.get('http://192.168.1.247/5')
class MyServer(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header("Content-type", "text/html")
        self.end_headers()
        print(self.path)
        if (self.path=="/1"):
            self.wfile.write(bytes(str(a),"utf-8"))
            val1 = requests.get('http://192.168.1.247/1')
            print(val1.text)
        if (self.path=="/2"):
            self.wfile.write(bytes(str(b),"utf-8"))
            val2 = requests.get('http://192.168.1.247/2')
            print(val2.text)
        if (self.path=="/3"):
            self.wfile.write(bytes(str(c),"utf-8"))
            val3 = requests.get('http://192.168.1.247/3')
            print(val3.text)
        if (self.path=="/4"):
            self.wfile.write(bytes(str(d),"utf-8"))
            val4 = requests.get('http://192.168.1.247/4')
            print(val4.text)
        if (self.path=="/5"):
            self.wfile.write(bytes(str(e),"utf-8"))
            val4 = requests.get('http://192.168.1.247/5')
            print(val5.text)
if __name__ == "__main__":        
    webServer = HTTPServer((hostName, serverPort), MyServer)
    print("Server started http://%s:%s" % (hostName, serverPort))

    try:
        webServer.serve_forever()
    except KeyboardInterrupt:
        pass

    webServer.server_close()
    #access_point.stop()
