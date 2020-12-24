import socket
import time

cts_socket=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serverIp='192.168.1.254'
ctsport=2500

while True:
    print('[CTS] Start Connecting to CTA')
    try:
        cts_socket.connect((serverIp, ctsport))
        print('[CTS] Connect : {}'.format(serverIp))
        break
    except:
        time.sleep(1)
        print('[CTS] Wating CTA Connection 1s...!')
        continue

while True:
    tc=input('[CTS] Sending TC : ')
    if not tc:
        continue

    try:
        cts_socket.send(tc.encode())    #send tc num
    except:
        print('[CTS] except send END!')
        break
    try:
        retMessage = cts_socket.recv(1024)
        if not retMessage:
            print("[CTS] retMessage is null!!")
        else:
            print(f'[CTS] RCV MSG : {retMessage.decode()}')
    except:
        print('[CTS] except Connection END')
        brea

cts_socket.close()


