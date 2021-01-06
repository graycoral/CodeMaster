import time
import threading
from someip.packet_generator import *

RECEIVE = "[TESTER <<< TARGET] "
SEND = "[TESTER >>> TARGET] "


class CreateFindService:
    def __init__(self, service_list):
        self.l_services = []
        self.stop_flag = False

        # SDPacketGenerator(0xffff, 0x8100, client_id, interface_version)
        self.find_packet = SDPacketGenerator(0xffff, 0x8100, 0x0000, 0x01)
        for service in service_list:
            # addServiceEntry(entry_type, service_id, instance_id, major_version, ttl, minor_version)
            self.find_packet.addServiceEntry('FIND', 0, 0, service['service'], 0xffff, 0xff, service['ttl'], 0xffffffff)
            if service['service'] not in self.l_services:
                self.l_services.append(service['service'])

        # make payload
        options_length = self.find_packet.getOptionSize()
        options = self.find_packet.makeSDOption()

        entries_length = self.find_packet.getEntrySize()
        entries = self.find_packet.makeEntry()

        # TODO : flags temporary set to 'c0'
        self.payload = 'c0' + (RESERVED * 3) + entries_length + entries + options_length + options

    def startFindService(self, interval):
        find_thread = threading.Thread(target=self.sendFind, args=(interval,))
        find_thread.daemon = True
        find_thread.start()

    def sendFind(self, interval):
        while not self.stop_flag:
            # make sd_header
            self.find_packet.increaseSessionId()
            self.find_packet.someipHeaderBind(self.payload, 'NOTIFICATION', 'E_OK')
            self.find_packet.sendSomeipMessage(sd_socket, multicast_address, SD_PORT)
            print(SEND + "send find: [service id]", self.l_services)
            time.sleep(interval / 1000)

    def stopFind(self):
        self.stop_flag = True


class CreateOfferService:
    def __init__(self, service_list):
        self.l_services = []
        self.stop_flag = False

        # SDPacketGenerator(0xffff, 0x8100, client_id, interface_version)
        self.offer_packet = SDPacketGenerator(0xffff, 0x8100, 0x0000, 0x01)
        # TODO: option_index2 설정
        self.option_index1 = 0
        self.option_index2 = 0
        for service in service_list:
            if ip_version == 6:
                # TODO : other option type 처리
                opt_type = "IPv6_EP"
            elif ip_version == 4:
                opt_type = "IPv4_EP"
            self.option_index1 = self.offer_packet.addEndpointOption(service['options']['protocol'],
                                                                     service['options']['port_number'],
                                                                     opt_type, src_addr_byte_str)
            # addServiceEntry(entry_type, service_id, instance_id, major_version, ttl, minor_version)
            self.offer_packet.addServiceEntry('OFFER', self.option_index1, self.option_index2, service['service'],
                                              service['instance'], service['major_version'], service['ttl'],
                                              service['minor_version'])
            if service['service'] not in self.l_services:
                self.l_services.append(service['service'])

        # make payload
        options_length = self.offer_packet.getOptionSize()
        options = self.offer_packet.makeSDOption()

        entries_length = self.offer_packet.getEntrySize()
        entries = self.offer_packet.makeEntry()

        # TODO : flags temporary set to 'c0'
        self.payload = 'c0' + (RESERVED * 3) + entries_length + entries + options_length + options

    def startOfferService(self, interval):
        offer_thread = threading.Thread(target=self.sendOffer, args=(interval,))
        offer_thread.daemon = True
        offer_thread.start()

    def sendOffer(self, interval):
        while not self.stop_flag:
            # make sd_header
            self.offer_packet.increaseSessionId()
            self.offer_packet.someipHeaderBind(self.payload, 'NOTIFICATION', 'E_OK')
            self.offer_packet.sendSomeipMessage(sd_socket, multicast_address, SD_PORT)
            print(SEND + "send offer: [service id]", self.l_services)
            time.sleep(interval / 1000)

    def stopOffer(self):
        self.stop_flag = True

class CreateSubscribe:
    def __init__(self, service):
        self.service = service
        self.subscribe_packet = SDPacketGenerator(0xffff, 0x8100, 0x0000, 0x01)
        self.entry_type = "SUBSCRIBE"
        if ip_version == 6:
            # TODO : other option type 처리
            self.opt_type = "IPv6_EP"
        elif ip_version == 4:
            self.opt_type = "IPv4_EP"
        self.option_index1 = self.subscribe_packet.addEndpointOption(service['options']['protocol'],
                                                                     service['options']['port_number'],
                                                                     self.opt_type, src_addr_byte_str)
        self.option_index2 = 0

        for idx in range(len(service['eventgroups'])):
            self.subscribe_packet.addEventGroupEntry(self.entry_type, self.option_index1, self.option_index2,
                                                     service["service"], service["instance"], service["major_version"],
                                                     service["ttl"], service["eventgroups"][idx]["eventgroup"])

        # make payload
        self.options_length = self.subscribe_packet.getOptionSize()
        self.options = self.subscribe_packet.makeSDOption()

        self.entries_length = self.subscribe_packet.getEntrySize()
        self.entries = self.subscribe_packet.makeEntry()

        # TODO : flags temporary set to 'c0'
        self.payload = 'c0' + (RESERVED * 3) + self.entries_length + self.entries + self.options_length + self.options

    def sendSubscribe(self, dst_address):
        # make sd_header
        self.subscribe_packet.increaseSessionId()
        self.subscribe_packet.someipHeaderBind(self.payload, 'NOTIFICATION', 'E_OK')

        for idx in range(len(self.service['eventgroups'])):
            print(SEND + "send subscribe: [service id " + self.service["service"] + "] " +
                  "[eventgroup id " + self.service["eventgroups"][idx]["eventgroup"] + "]")
        self.subscribe_packet.sendSomeipMessage(sd_socket, dst_address, SD_PORT)

    def stopSubscribe(self):
        # TODO: StopSubscribe
        pass


class CreateSubscribeAck:
    def __init__(self, service):
        self.service = service
        self.subscribe_ack_packet = SDPacketGenerator(0xffff, 0x8100, 0x0000, 0x01)
        self.entry_type = "SUBSCRIBE_ACK"

        # TODO : subscribeAck message is possible to have a multicast option or configuration, load balancing option
        # addEventGroupEntry(entry_type, index1, index2, entry_service_id,
        #                    instance_id, major_version, ttl, event_group_id)
        for idx in range(len(service['eventgroups'])):
            self.subscribe_ack_packet.addEventGroupEntry(self.entry_type, 0, 0, service["service"],
                                                        service["instance"], service["major_version"],
                                                        service["ttl"], service["eventgroups"][idx]["eventgroup"])

        # make payload
        self.options_length = self.subscribe_ack_packet.getOptionSize()
        self.options = self.subscribe_ack_packet.makeSDOption()

        self.entries_length = self.subscribe_ack_packet.getEntrySize()
        self.entries = self.subscribe_ack_packet.makeEntry()

        # TODO : flags temporary set to '00'
        self.payload = '00' + (RESERVED * 3) + self.entries_length + self.entries + self.options_length + self.options

    def sendSubscribeAck(self, dst_address):
        # make sd_header
        self.subscribe_ack_packet.increaseSessionId()
        self.subscribe_ack_packet.someipHeaderBind(self.payload, 'NOTIFICATION', 'E_OK')

        for idx in range(len(self.service['eventgroups'])):
            print(SEND + "send subscribe ack: [service id " + self.service['service'] + "] "
                  + "[eventgroup id" + self.service['eventgroups'][idx]['eventgroup'] + "]")
        self.subscribe_ack_packet.sendSomeipMessage(sd_socket, dst_address, SD_PORT)


class CreateRequest:
    def __init__(self, service, client_id):
        self.service = service
        keys = self.service.keys()
        if "methods" in keys:
            self.method_id = self.service["methods"][0]
        elif "eventgroups" in keys:
            self.method_id = self.service["eventgroups"][0]["events"][0]

        self.request_packet = SOMEIPPacketGenerator(self.service['service'], self.method_id,
                                                    client_id, service["major_version"])

    def sendRequest(self, payload, dst_address, dst_port):
        # TODO : session control(매번 새로운 객체를 생성 하여 session이 유지되지 않을 것 같다)
        session_id = self.request_packet.increaseSessionId()
        self.request_packet.someipHeaderBind(payload, 'REQUEST', 'E_OK')

        sock = someip_socket_bind(self.service['options']['port_number'])
        self.request_packet.sendSomeipMessage(sock, dst_address, dst_port)
        print(SEND + "send request message: [service id " + self.service['service'] + "] " +
              "[method id " + self.method_id + "]")
        return sock, session_id


class CreateResponse:
    def __init__(self, service, client_id):
        self.service = service
        keys = self.service.keys()
        if "methods" in keys:
            self.method_id = self.service["methods"][0]
        elif "eventgroups" in keys:
            self.method_id = self.service["eventgroups"][0]["events"][0]

        # SOMEIPPacketGenerator(service_id, method_id, client_id, interface_version)
        self.response_packet = SOMEIPPacketGenerator(self.service['service'], self.method_id,
                                                     client_id, self.service['major_version'])

    def sendResponse(self, payload, sock, session_id, endpoint):
        self.response_packet.session_id = valueToByteString(session_id, 2)

        self.response_packet.someipHeaderBind(payload, 'RESPONSE', 'E_OK')
        # TODO: endpoint 인자는 가독성이 떨어진다.
        self.response_packet.sendSomeipMessage(sock, endpoint[0], endpoint[1])
        print(
            SEND + "send response message: [service id " + self.service['service'] + "] " +
            "[method id " + self.method_id + "]")


class CreateEvent:
    def __init__(self, service):
        self.service = service
        # SOMEIPPacketGenerator(service_id, method_id, client_id, interface_version)
        # TODO : eventgroup and event 순회 : checkSubscribe에서 event group id 를 저장하고 전달 해주는 방법 검토
        # checkSubscribeAck과 같은 방법으로 subscribe를 받은 event group을 check하고 check element가 있는 경우 send
        # send후 evnet group pop
        self.notification_packet = SOMEIPPacketGenerator(self.service["service"],
                                                         self.service["eventgroups"][0]["events"][0], 0x0000,
                                                         self.service["major_version"])
        self.sock = someip_socket_bind(self.service['options']['port_number'])

    def sendEvent(self, payload, dst_address, dst_port):
        self.notification_packet.increaseSessionId()
        self.notification_packet.someipHeaderBind(payload, 'NOTIFICATION', 'E_OK')
        self.notification_packet.sendSomeipMessage(self.sock, dst_address, dst_port)
        print(SEND + "send event message: [service id " + self.service['service'] + "] "
              + "[method id " + self.service["eventgroups"][0]["events"][0] + "]")


class ReceiveMessage:
    def __init__(self, sock):
        self.dst_option = ''
        self.dst_address = "localhost"
        self.dst_port = 0
        # self.someip_sock = None

        self.r_msg, self.r_addr = SOMEIPPacketGenerator(0, 0, 0, 0).receiveSomeipMessage(sock)
        self.parsed_packet = PacketParser(self.r_msg)

    def checkSubscribe(self, service):
        for s_entry in self.parsed_packet.entryArray:
            rcv_entry = EntryArrayParser(s_entry)
            # TODO: event group 순환 검색
            if rcv_entry.entry_type == ENTRY_TYPE['SUBSCRIBE'] \
                    and rcv_entry.entry_service_id == valueToByteString(service["service"], 2) \
                    and rcv_entry.instance_id == valueToByteString(service["instance"], 2) \
                    and rcv_entry.major_version == valueToByteString(service["major_version"], 1) \
                    and rcv_entry.event_group_id == valueToByteString(service["eventgroups"][0]["eventgroup"], 2):
                # TODO: process multi Endpoint option of subscribe message
                # limitation : save last endpoint option
                self.dst_option = OptionArrayParser(self.parsed_packet.optionArray[int(rcv_entry.opt_idx1, 16)])
                self.dst_address = str(ipaddress.ip_address(int(self.dst_option.ip_address, 16)))
                self.dst_port = int(self.dst_option.port_number, 16)

                if self.dst_option.protocol != L4PROTOCOL[service['options']['protocol']] \
                        or self.dst_option.port_number != valueToByteString(service['options']['port_number'], 2):
                    print("[Warning][checkSubscribe]: miss-match option information")

                print(RECEIVE + "receive subscribe : [service id 0x" + rcv_entry.entry_service_id + "] "
                      + "[eventgroup id 0x" + rcv_entry.event_group_id + "]")
                return True
        return False

    def checkSubscribeAck(self, service):
        for s_entry in self.parsed_packet.entryArray:
            rcv_entry = EntryArrayParser(s_entry)
            # TODO: event group 순환 검색
            if rcv_entry.entry_type == ENTRY_TYPE['SUBSCRIBE_ACK'] \
                    and rcv_entry.entry_service_id == valueToByteString(service["service"], 2) \
                    and rcv_entry.instance_id == valueToByteString(service["instance"], 2) \
                    and rcv_entry.major_version == valueToByteString(service["major_version"], 1):
                for idx, eventgroup_list in enumerate(service['eventgroups']):
                    if rcv_entry.event_group_id == valueToByteString(eventgroup_list['eventgroup'], 2):
                        eventgroup_list['check'] = True
                        if rcv_entry.ttl == '000000':
                            print(RECEIVE + "receive subscribe Nack: [service id " + service['service'] + "] "
                                  + "[eventgroup id " + service['eventgroups'][idx]['eventgroup'] + "]")
                            return "NACK"
                        else:
                            print(RECEIVE + "receive subscribe ack: [service id " + service['service'] + "] "
                                  + "[eventgroup id " + service['eventgroups'][idx]['eventgroup'] + "]")
                            return "ACK"
                # self.someip_sock = someip_socket_bind(service['options']['port_number'])
        return None

    def checkOffer(self, service):
        for s_entry in self.parsed_packet.entryArray:
            rcv_entry = EntryArrayParser(s_entry)
            if rcv_entry.entry_type == ENTRY_TYPE['OFFER'] \
                    and rcv_entry.entry_service_id == valueToByteString(service["service"], 2) \
                    and rcv_entry.instance_id == valueToByteString(service["instance"], 2) \
                    and rcv_entry.major_version == valueToByteString(service["major_version"], 1) \
                    and rcv_entry.minor_version == valueToByteString(service["minor_version"], 4):
                # TODO: process multi Endpoint option of offer message
                # limitation: Not support Number of opt
                self.dst_option = OptionArrayParser(self.parsed_packet.optionArray[int(rcv_entry.opt_idx1, 16)])
                self.dst_address = str(ipaddress.ip_address(int(self.dst_option.ip_address, 16)))
                self.dst_port = int(self.dst_option.port_number, 16)

                if self.dst_option.protocol != L4PROTOCOL[service['options']['protocol']] \
                        or self.dst_option.port_number != valueToByteString(service['options']['port_number'], 2):
                    print("[Warning][checkOffer]: miss-match option information")

                print(RECEIVE + "found offer: [service id 0x" + rcv_entry.entry_service_id + "]")
                return True
        return False

    def checkEvent(self, service):
        for idx in range(len(service['eventgroups'])):
            if self.parsed_packet.message_id == (valueToByteString(service['service'], 2) +
                                                 valueToByteString(service["eventgroups"][idx]["events"][0], 2)) \
                    and self.parsed_packet.packet_len == valueToByteString(((len(self.parsed_packet.payload) / 2) + 8), 4) \
                    and self.parsed_packet.client_id == valueToByteString(0, 2) \
                    and self.parsed_packet.protocol_ver == '01' \
                    and self.parsed_packet.interface_ver == valueToByteString(service['major_version'], 1) \
                    and self.parsed_packet.message_type == MESSAGE_TYPE['NOTIFICATION'] \
                    and self.parsed_packet.ret_code == RETURN_CODE['E_OK'] \
                    and 'check' in service['eventgroups'][idx]:
                print(RECEIVE + "receive event message: [service id " + service['service'] + "] " + "[method id "
                      + service["eventgroups"][idx]["events"][0] + "]")
                service['eventgroups'].pop(idx)
                return True
        return False

    def checkRequest(self, service):
        method_id = ''
        keys = service.keys()
        if "methods" in keys:
            method_id = service["methods"][0]
        elif "eventgroups" in keys:
            method_id = service["eventgroups"][0]["events"][0]
        if self.parsed_packet.message_id == (valueToByteString(service['service'], 2) +
                                             valueToByteString(method_id, 2)) \
                and self.parsed_packet.protocol_ver == valueToByteString(1, 1) \
                and self.parsed_packet.interface_ver == valueToByteString(service['major_version'], 1) \
                and self.parsed_packet.message_type == MESSAGE_TYPE['REQUEST'] \
                and self.parsed_packet.ret_code == RETURN_CODE['E_OK']:
            self.session_id = int(self.parsed_packet.session_id, 16)
            self.client_id = int(self.parsed_packet.client_id, 16)
            print(RECEIVE + "receive request message: [service id " + service['service'] + "] " + "[method id "
                  + method_id + "]")
            return True
        return False

    def checkResponse(self, service, client_id, session_id):
        method_id = ''
        keys = service.keys()
        if "methods" in keys:
            method_id = service["methods"][0]
        elif "eventgroups" in keys:
            method_id = service["eventgroups"][0]["events"][0]
        if \
                self.parsed_packet.message_id == (valueToByteString(service['service'], 2) +
                                                  valueToByteString(method_id, 2)) \
                and self.parsed_packet.client_id == valueToByteString(client_id, 2) \
                and self.parsed_packet.session_id == valueToByteString(session_id, 2) \
                and self.parsed_packet.protocol_ver == valueToByteString(1, 1) \
                and self.parsed_packet.interface_ver == valueToByteString(service['major_version'], 1) \
                and self.parsed_packet.message_type == MESSAGE_TYPE['RESPONSE'] \
                and self.parsed_packet.ret_code == RETURN_CODE['E_OK']:
            print(RECEIVE + "receive response message: [service id " + service['service'] + "] " + "[method id "
                  + method_id + "]")
            return True
        return False
