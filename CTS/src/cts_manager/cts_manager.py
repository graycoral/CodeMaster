'''
CTS connector implementation
'''

import time
import socket
import struct
import ipaddress
import logging
import _thread
import threading


dataFormat = '='

dataFormat += 'b'  # bool
# dataFormat += '20s' # string 20 byte

class CtsManager:
    def __init__(self, lock, logger):
        self.lock = lock
        self.logger_ = logger
        self.check_received_message = False

    def process_initial_cts_manager(self, ip_address, cts_port):
        self.logger_.info('Start Connecting to CTA')
        while True:
            try:
                self.cts_socket = socket.create_connection((ip_address, cts_port))
                break
            except:
               time.sleep(1)
               self.logger_.info('Waiting CTA Connection 1s...!')
               continue
        self.logger_.info('Connected : {}'.format(ip_address))
        _thread.start_new_thread(self.handler, ())

    def socket_close(self):
        self.cts_socket.close()

    def send_test_case(self, tc):
        self.logger_.info('Sending TC : {}'.format(tc))
        self.lock.acquire()
        try:
            self.cts_socket.sendall(str(tc).encode())  # send tc num
        except:
            self.logger_.error('except send END!')

    def handler(self):
        tc_result = struct.Struct(dataFormat)
        while True:
            try:
                retMessage = self.cts_socket.recv(1)
                if not retMessage:
                    self.logger_.error("retMessage is null!!")
                else:
                    result = tc_result.unpack(retMessage)
                    self.logger_.info('RCV MSG(unpack) : {}'.format(result[0]))
                    break
            except:
                self.logger_.error('except Connection END')
                break
        self.lock.release()
        self.check_received_message = True

    def wait_message(self):
        while True:
            if self.check_received_message is True:
                self.check_received_message = False
                break


