import time
from socket import *

port = 2500
BUFSIZE = 1024

fake_cta_socket=socket(AF_INET, SOCK_STREAM)
fake_cta_socket.bind(('192.168.1.254', port))

fake_cta_socket.listen(5)

print('[FCTA] Waiting CTS!!')
c_sock, (r_host, r_port) = fake_cta_socket.accept()
print('[FCTA] Connected CTS!!')

while True:
    try:
        print('[FCTA] Wating TC Num from CTS...')
        data = c_sock.recv(BUFSIZE)
        if not data:
            c_sock.close()
            print('[FCTA] END CONNECTION')
            break
    except:
        print('[FCTA] except rcv data END CONNECTION')
        break
    else:
        print(f'[FCTA] RCV MSG : {data.decode()}')

    try:
        result = input('[FCTA] Return result : ')
        c_sock.send(result.encode())
    except:
        print('[FCTA] except result send END CONNECTION')
        c_sock.close()
        break

c_sock.close()
fake_cta_socket.close()