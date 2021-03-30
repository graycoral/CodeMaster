import socket
import struct
import ipaddress
import json
import os

CONFIG_FILE = os.path.dirname(os.path.abspath(__file__))
CONFIG_FILE += '/../../config.json'

with open(CONFIG_FILE) as config_file:
    config_data = json.load(config_file)
    src_address = config_data["unicast"]
    multicast_address = config_data["multicast"]
    tc_com = config_data["TC_COM"]

SD_PORT = 30490

addr = ipaddress.ip_address(src_address)
if addr.version == 6:
    ip_version = 6
    src_addr_byte_str = format(int(addr), 'x').zfill(32)
    family = socket.AF_INET6
    opt_level = socket.IPPROTO_IPV6
    opt_member = socket.IPV6_JOIN_GROUP
    opt_loop = socket.IPV6_MULTICAST_LOOP
    mreq = struct.pack("16s15s".encode('utf-8'), socket.inet_pton(socket.AF_INET6, multicast_address),
                       (chr(0) * 16).encode('utf-8'))
elif addr.version == 4:
    ip_version = 4
    src_addr_byte_str = format(int(addr), 'x').zfill(8)
    family = socket.AF_INET
    opt_level = socket.IPPROTO_IP
    opt_member = socket.IP_ADD_MEMBERSHIP
    opt_loop = socket.IP_MULTICAST_LOOP
    mreq = struct.pack("4sl".encode('utf-8'), socket.inet_aton(multicast_address), socket.INADDR_ANY)
else:
    print("invalid ip address in config.json file")
    family = -1
    opt_level = -1
    opt_member = -1
    opt_loop = -1
    mreq = ""
    exit(0)

# TODO: TCP socket
rcv_multicast_socket = socket.socket(family, socket.SOCK_DGRAM)
rcv_multicast_socket.setsockopt(opt_level, opt_loop, False)
# rcv_multicast_socket.setsockopt(opt_level, socket.IPV6_MULTICAST_HOPS, 4)
rcv_multicast_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
rcv_multicast_socket.bind(('', SD_PORT))
rcv_multicast_socket.setsockopt(opt_level, opt_member, mreq)

sd_socket = socket.socket(family, socket.SOCK_DGRAM)
sd_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
sd_socket.bind((src_address, SD_PORT))


def someip_socket_bind(endpoint_port):
    someip_socket = socket.socket(family, socket.SOCK_DGRAM)
    someip_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    someip_socket.bind((src_address, endpoint_port))
    return someip_socket
