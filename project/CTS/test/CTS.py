import socket
import time
import struct

cts_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serverIp = '192.168.7.4'
ctsport = 2500

# while True:
#     print('[CTS] Start Connecting to CTA')
#     try:
#         cts_socket.connect((serverIp, ctsport))
#         print('[CTS] Connect : {}'.format(serverIp))
#         break
#     except:
#         time.sleep(1)
#         print('[CTS] Wating CTA Connection 1s...!')
#         continue

# while True:
#     tc=input('[CTS] Sending TC : ')
#     if not tc:
#         continue

#     try:
#         cts_socket.send(tc.encode())    #send tc num
#     except:
#         print('[CTS] except send END!')
#         break
#     try:
#         retMessage = cts_socket.recv(1024)
#         if not retMessage:
#             print("[CTS] retMessage is null!!")
#         else:
#             print('[CTS] RCV MSG : {}'.format(retMessage.decode()))
#             break
#     except:
#         print('[CTS] except Connection END')
#         break

# cts_socket.close()


import binascii

MCAST_GRP = '224.1.1.1'
MCAST_PORT = 5007


def main():
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
    try:
        sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    except AttributeError:
        pass
    sock.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_TTL, 32)
    sock.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_LOOP, 1)

    sock.bind((MCAST_GRP, MCAST_PORT))
    host = socket.gethostbyname(socket.gethostname())
    sock.setsockopt(socket.SOL_IP, socket.IP_MULTICAST_IF, socket.inet_aton(host))
    sock.setsockopt(socket.SOL_IP, socket.IP_ADD_MEMBERSHIP,
                    socket.inet_aton(MCAST_GRP) + socket.inet_aton(host))

    while 1:
        try:
            data, addr = sock.recvfrom(1024)
        except socket.error as e:
            print('Expection')
            hexdata = binascii.hexlify(data)
            print('Data = %s' % hexdata)


if __name__ == '__main__':
    main()
