import socket
import ipaddress

class TrafficLight:

    def __init__(self, ip='', port=8888):
        self.ip = ip
        self.port = port
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    def red(self):
        self.socket.sendto(b'1', (self.ip, self.port))

    def yellow(self):
        self.socket.sendto(b'2', (self.ip, self.port))

    def green(self):
        self.socket.sendto(b'3', (self.ip, self.port))

    def clear(self):
        self.socket.sendto(b'4', (self.ip, self.port))


class TrafficManager():

    def __init__(self, ip='192.168.4.1'):
        self.ip = ipaddress.IPv4Address(ip)
        self.broadcast = self.ip.broadcast_address
        print(self.ip, self.broadcast)
        self.trafficlights = []
