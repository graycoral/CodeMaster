import os
import socket
import threading
import logging

from inspect import currentframe, getframeinfo

from conf.netconf import *
from res.json_result import *
from conf.readConfig import *
from someip.packet_comm import *
from cts_manager.cts_manager import CtsManager
from testcase import *


# Test TC_CM_001
# [TESTER <<< TARGET] found offer
# [TESTER >>> TARGET] send subscribe
# [TESTER <<< TARGET] receive subscribe ack
# [TESTER <<< TARGET] receive event message

def TC_CM_001():
    f_info = getframeinfo(currentframe())
    function_name = f_info.function
    service_list = tc_com[f_info.function][1:]

    retry_count = 5

    while retry_count:
        try:
            if len(service_list) == 0:
                print(function_name + " Done")
                return True

            rcv_offer_packet = ReceiveMessage(rcv_multicast_socket)

            for service in service_list:
                if rcv_offer_packet.checkOffer(service):
                    checkResult(function_name, service['service'], "offer")
                    subs_packet = CreateSubscribe(service)
                    subs_packet.sendSubscribe(rcv_offer_packet.dst_address)
                    rcv_subs_ack_packet = ReceiveMessage(sd_socket)
                    if rcv_subs_ack_packet.checkSubscribeAck(service) == "ACK":
                        checkResult(function_name, service['service'], "subscribeAck")
                    someip_sock = someip_socket_bind(service['options']['port_number'])
                    rcv_event_message = ReceiveMessage(someip_sock)
                    if rcv_event_message.checkEvent(service):
                        checkResult(function_name, service['service'], "event")
                        if len(service['eventgroups']) == 0:
                            service_list.remove(service)
                            # TODO : stopSubscribe
            retry_count -= 1
        except socket.timeout:
            print("socket timeout")
            break
        except UnboundLocalError:
            print("UnboundLocalError")
            break

    print(function_name + " Fail")
    return False


# Test TC_CM_002
# [TESTER <<< TARGET] found offer
# [TESTER >>> TARGET] send subscribe
# [TESTER <<< TARGET] receive subscribe ack
# [TESTER <<< TARGET] receive event message
def TC_CM_002():
    f_info = getframeinfo(currentframe())
    function_name = f_info.function
    service_list = tc_com[f_info.function][1:]

    retry_count = 10
    while retry_count:
        try:
            if len(service_list) == 0:
                print(function_name + " Done")
                return True

            rcv_offer_packet = ReceiveMessage(rcv_multicast_socket)

            for service in service_list:
                if rcv_offer_packet.checkOffer(service):
                    checkResult(function_name, service['service'], "offer")
                    subs_packet = CreateSubscribe(service)
                    subs_packet.sendSubscribe(rcv_offer_packet.dst_address)
                    rcv_subs_ack_packet = ReceiveMessage(sd_socket)
                    if rcv_subs_ack_packet.checkSubscribeAck(service) == 'ACK':
                        # TODO: checkResult를 event group 별로 구분
                        checkResult(function_name, service['service'], "subscribeAck")
                        someip_sock = someip_socket_bind(service['options']['port_number'])
                        rcv_event_message = ReceiveMessage(someip_sock)
                        # TODO: notification initial event message 확인
                        # TODO: polling vs event driven 동작 비교 확인
                        if rcv_event_message.checkEvent(service):
                            checkResult(function_name, rcv_event_message.parsed_packet.message_id, "notification")
                            if len(service['eventgroups']) == 0:
                                service_list.remove(service)
            retry_count -= 1
        except socket.timeout:
            print("socket timeout")
            break
        except UnboundLocalError:
            print("UnboundLocalError")
            break
    print(function_name + " Fail")
    return False


# Test TC_CM_003
# [TESTER >>> TARGET] send find
# [TESTER <<< TARGET] found offer
# [TESTER >>> TARGET] send subscribe
# [TESTER <<< TARGET] receive subscribe Nack
def TC_CM_003():
    interval = 2000
    f_info = getframeinfo(currentframe())
    function_name = f_info.function
    service_list = tc_com[f_info.function][1:]

    offer_found = False
    find_service = CreateFindService(service_list)
    find_service.startFindService(interval)

    while not offer_found:
        try:
            rcv_offer_packet = ReceiveMessage(sd_socket)
        except socket.timeout:
            print("sd_socket timeout : offer packet wait")
            print("TC_CM_003 Fail")
            find_service.stopFind()
            return
        else:
            if rcv_offer_packet.checkOffer(service_list[0]):
                checkResult(function_name, service_list[0]['service'], "offer")
                offer_found = True
                find_service.stopFind()

    subs_packet = CreateSubscribe(service_list[0])
    subs_packet.sendSubscribe(rcv_offer_packet.dst_address)

    while True:
        try:
            rcv_subscribe_nack_packet = ReceiveMessage(sd_socket)
        except socket.timeout:
            print("sd_socket timeout : subscribeNack packet wait")
            break
        else:
            if rcv_subscribe_nack_packet.checkSubscribeAck(service_list[0]) == 'NACK':
                checkResult(function_name, service_list[0]['service'], "subscribeNack")
                print("TC_CM_003 OK")
                return
            # TODO: else의 경우 다시 offer receive 부터 시작 해야 함

    print("TC_CM_003 Fail")


# Test TC_CM_004
# [TESTER <<< TARGET] found offer
# [TESTER >>> TARGET] send request message
# [TESTER <<< TARGET] receive response message
def TC_CM_004():
    payload_list = ['0000008200000156000001be']  # payload: x = 00000082, y = 00000156, z = 000001be
    client_id = 0x00
    f_info = getframeinfo(currentframe())
    function_name = f_info.function
    service_list = tc_com[f_info.function][1:]

    offer_found = False

    while not offer_found:
        try:
            # print("wait offer service")
            rcv_offer_packet = ReceiveMessage(rcv_multicast_socket)
        except socket.timeout:
            print("multicast_socket timeout")
            print("TC_CM_004 Fail")
            return
        else:
            if rcv_offer_packet.checkOffer(service_list[0]):
                checkResult(function_name, service_list[0]['service'], "offer")
                offer_found = True

    request_packet = CreateRequest(service_list[0], client_id)
    for payload in payload_list:
        someip_sock, session_id = request_packet.sendRequest(payload, rcv_offer_packet.dst_address,
                                                             rcv_offer_packet.dst_port)
        try:
            rcv_response_packet = ReceiveMessage(someip_sock)
        except socket.timeout:
            print("someip_socket timeout")
            break
        except UnboundLocalError:
            print("UnboundLocalError")
            break
        else:
            if rcv_response_packet.checkResponse(service_list[0], client_id, session_id):
                checkResult(function_name, service_list[0]['service'], "response")
                print("TC_CM_004 OK")
                return

    print("TC_CM_004 Fail")


# Test TC_CM_005
# [TESTER <<< TARGET] found offer
# [TESTER >>> TARGET] send request message
# [TESTER <<< TARGET] receive response message
def TC_CM_005():
    payload_list = ['', '0100']
    client_id = 0x1234
    f_info = getframeinfo(currentframe())
    function_name = f_info.function
    service_list = tc_com[f_info.function][1:]

    retry_count = 10

    while retry_count:
        try:
            if len(service_list) == 0:
                print(function_name + " Done")
                return True

            rcv_offer_packet = ReceiveMessage(rcv_multicast_socket)

            for idx, service in enumerate(service_list):
                if rcv_offer_packet.checkOffer(service):
                    checkResult(function_name, service['service'], "offer")
                    request_packet = CreateRequest(service, client_id)
                    someip_sock, session_id = request_packet.sendRequest(payload_list[idx],
                                                                         rcv_offer_packet.dst_address,
                                                                         rcv_offer_packet.dst_port)

                    rcv_response_packet = ReceiveMessage(someip_sock)
                    if rcv_response_packet.checkResponse(service, client_id, session_id):
                        checkResult(function_name, rcv_response_packet.parsed_packet.message_id, "response")
                        # TODO: multi event group 처리
                        service_list.remove(service)
                        payload_list.pop(idx)
            retry_count -= 1
        except socket.timeout:
            print("someip_socket timeout")
            break
        except UnboundLocalError:
            print("UnboundLocalError")
            break

    print(function_name + " Fail")
    return False


# Test TC_CM_007
# [TESTER >>> TARGET] send offer
# [TESTER <<< TARGET] receive subscribe
# [TESTER >>> TARGET] send subscribe ack
# [TESTER >>> TARGET] send event message

def TC_CM_007():
    payload_list = ['0100000001be']
    offer_cycle = 2000
    f_info = getframeinfo(currentframe())
    function_name = f_info.function
    service_list = tc_com[f_info.function][1:]

    offer_service = CreateOfferService(service_list)
    offer_service.startOfferService(offer_cycle)

    retry_count = 10

    while retry_count:
        if len(service_list) == 0:
            print(function_name + " Done")
            offer_service.stopOffer()
            return True

        try:
            rcv_subscribe_packet = ReceiveMessage(sd_socket)
            for idx, service in enumerate(service_list):
                if rcv_subscribe_packet.checkSubscribe(service):
                    checkResult(function_name, service["service"], "offer")
                    subs_ack_packet = CreateSubscribeAck(service)
                    subs_ack_packet.sendSubscribeAck(rcv_subscribe_packet.dst_address)
                    # TODO: session handling 안됨
                    event_packet = CreateEvent(service)
                    event_packet.sendEvent(payload_list[idx], rcv_subscribe_packet.dst_address,
                                           rcv_subscribe_packet.dst_port)
                    service_list.remove(service)
                    payload_list.pop(idx)
        except socket.timeout:
            print("socket timeout")
            break
        retry_count -= 1

    print(function_name + " Fail")
    offer_service.stopOffer()
    return False


# Test TC_CM_008
# [TESTER >>> TARGET] send offer
# [TESTER <<< TARGET] receive subscribe
# [TESTER >>> TARGET] send subscribe ack
# [TESTER >>> TARGET] send event message
def TC_CM_008():
    # skeleton
    payload_list = ['000222e0']
    offer_cycle = 2000
    f_info = getframeinfo(currentframe())
    function_name = f_info.function
    service_list = tc_com[f_info.function][1:]

    offer_service = CreateOfferService(service_list)
    offer_service.startOfferService(offer_cycle)

    service1 = False
    retry_count = 5  # 5번 receive packet 수신
    while retry_count:
        try:
            rcv_subscribe_packet = ReceiveMessage(sd_socket)
        except socket.timeout:
            print("socket timeout")
            break
        else:
            if rcv_subscribe_packet.checkSubscribe(service_list[0]):
                checkResult(function_name, service_list[0]['service'], "subscribe")
                subs_ack_packet = CreateSubscribeAck(service_list[0])
                subs_ack_packet.sendSubscribeAck(rcv_subscribe_packet.dst_address)
                event_packet = CreateEvent(service_list[0])
                for payload in payload_list:
                    # sendEvent(payload, service, dst_address, dst_port)
                    event_packet.sendEvent(payload, rcv_subscribe_packet.dst_address, rcv_subscribe_packet.dst_port)
                service1 = True
            retry_count -= 1
            if service1:
                print("TC_CM_008 OK")
                offer_service.stopOffer()
                return

    print("TC_CM_008 Fail")
    offer_service.stopOffer()


# Test TC_CM_009
# [TESTER >>> TARGET] send offer
# [TESTER <<< TARGET] receive request message
# [TESTER >>> TARGET] send response message
def TC_CM_009():
    payload_list = ['010000008200000156000001be']  # active = 01
    offer_cycle = 2000
    f_info = getframeinfo(currentframe())
    function_name = f_info.function
    service_list = tc_com[f_info.function][1:]

    offer_service = CreateOfferService(service_list)
    offer_service.startOfferService(offer_cycle)

    someip_socket = someip_socket_bind(service_list[0]['options']['port_number'])

    while True:
        try:
            rcv_request_packet = ReceiveMessage(someip_socket)
            if rcv_request_packet.checkRequest(service_list[0]):
                checkResult(function_name, service_list[0]['service'], "request")
                response_packet = CreateResponse(service_list[0], rcv_request_packet.client_id)
                for payload in payload_list:
                    response_packet.sendResponse(payload, someip_socket,
                                                 rcv_request_packet.session_id, rcv_request_packet.r_addr)
                print("TC_CM_009 OK")
                offer_service.stopOffer()
                return True

        except socket.timeout:
            print("someip_socket timeout")
            break

    print("TC_CM_009 Fail")
    offer_service.stopOffer()
    someip_socket.close()
    return False


# Test TC_CM_012
# [TESTER >>> TARGET] send offer
# [TESTER <<< TARGET] receive request message(getter)
# [TESTER >>> TARGET] send response message
# [TESTER <<< TARGET] receive request message(setter)
def TC_CM_012():
    payload_list = ['0100']  # 256(uint16)
    offer_cycle = 2000
    f_info = getframeinfo(currentframe())
    function_name = f_info.function
    service_list = tc_com[f_info.function][1:]

    service_result = [False for _ in range(len(service_list))]

    offer_service = CreateOfferService(service_list)
    offer_service.startOfferService(offer_cycle)

    getter_socket = someip_socket_bind(service_list[0]['options']['port_number'])

    while True:
        try:
            rcv_request_packet = ReceiveMessage(getter_socket)
            if not service_result[0] and rcv_request_packet.checkRequest(service_list[0]):
                checkResult(function_name, service_list[0]['service'], "request")
                response_packet = CreateResponse(service_list[0], rcv_request_packet.client_id)
                for payload in payload_list:
                    response_packet.sendResponse(payload, getter_socket,
                                                 rcv_request_packet.session_id, rcv_request_packet.r_addr)
                service_result[0] = True
            elif not service_result[1] and rcv_request_packet.checkRequest(service_list[1]):
                checkResult(function_name, service_list[1]['service'], "request")
                # TODO : setter도 sendResponse가 필요?
                service_result[1] = True

            if False not in service_result:
                print("TC_CM_012 OK")
                offer_service.stopOffer()
                getter_socket.close()
                return True

        except socket.timeout:
            print("someip_socket timeout")
            break

    print("TC_CM_012 Fail")
    offer_service.stopOffer()
    getter_socket.close()
    return False


TC = {"TC_CM_001": TC_CM_001, "TC_CM_002": TC_CM_002, "TC_CM_003": TC_CM_003, "TC_CM_004": TC_CM_004,
      "TC_CM_005": TC_CM_005, "TC_CM_007": TC_CM_007, "TC_CM_008": TC_CM_008, "TC_CM_009": TC_CM_009,
      "TC_CM_012": TC_CM_012}

CONFIG_FILE_PATH = os.path.dirname(os.path.abspath(__file__)) + '/../../config.json'

class TestCase:
    def __init__(self, logger):
        self.configJson = ConfigJson(CONFIG_FILE_PATH)
        self.test_case_list = list()
        self.add_test_case(list(self.configJson.testData.keys()))
        self.lock = threading.Lock()
        self.logger_ = logger
        self.cts_manager = CtsManager(self.lock, logger)
        self.connect_cta()

    def add_test_case(self, testcases):
        for tc in testcases:
            self.test_case_list.append(TC[tc])

    def get_test_case(self):
        return self.test_case_list

    def run_test_case(self, idx):
        if len(self.test_case_list) > idx:
            self.cts_manager.send_test_case(list(TC)[idx])
            self.test_case_list[idx]()
            self.cts_manager.wait_message()
        else:
            self.logger_.error("Invalid Test Index")

    def read_test_case_all_desc(self):
        self.configJson.ReadAllDesc()

    def read_test_case_desc(self, idx):
        self.configJson.ReadTestCaseDesc(idx)

    def connect_cta(self):
        self.cts_manager.process_initial_cts_manager(self.configJson.cts_ipaddress, self.configJson.cts_port)