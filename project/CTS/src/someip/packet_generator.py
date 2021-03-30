import binascii

RESERVED = '00'

MESSAGE_TYPE = {'REQUEST': '00', 'REQUEST_NO_RETURN': '01', 'NOTIFICATION': '02',
                'RESPONSE': '80', 'ERROR': '81', 'TP_REQUEST': '20', 'TP_REQUEST_NO_RETURN': '21',
                'TP_NOTIFICATION': '22', 'TP_RESPONSE': 'a0', 'TP_ERROR': 'a1'}
RETURN_CODE = {'E_OK': '00', 'E_NOT_OK': '01', 'E_UNKNOWN_SERVICE': '02', 'E_UNKNOWN_METHOD': '03',
               'E_NOT_READY': '04', 'E_NOT_REACHABLE': '05', 'E_TIMEOUT': '06',
               'E_WRONG_PROTOCOL_VERSION': '07', 'E_WRONG_INTERFACE_VERSION': '08', 'E_MALFORMED_MESSAGE': '09',
               'E_WRONG_MESSAGE_TYPE': '0a', 'E_E2E_REPEATED': '0b', 'E_E2E_WRONG_SEQUENCE': '0c',
               'E_E2E': '0d', 'E_E2E_NOT_AVAILABLE': '0e', 'E_E2E_NO_NEW_DATA': '0f'}

OPT_LENGTH = {'LoadBalancing': '0005', 'IPv4_EP': '0009', 'IPv6_EP': '0015', 'IPv4_Multi': '0009',
              'IPv6_Multi': '0015', 'IPv4_SD_EP': '0009', 'IPv6_SD_EP': '0015'}
OPT_TYPE = {'Configuration': '01', 'LoadBalancing': '02', 'IPv4_EP': '04', 'IPv6_EP': '06', 'IPv4_Multi': '14',
            'IPv6_Multi': '16', 'IPv4_SD_EP': '24', 'IPv6_SD_EP': '26'}
L4PROTOCOL = {'TCP': '06', 'UDP': '11'}
ENTRY_TYPE = {'FIND': '00', 'OFFER': '01', 'SUBSCRIBE': '06', 'SUBSCRIBE_ACK': '07'}


def valueToByteString(value, byte):
    byte_format = '{0:0' + str(int(byte * 2)) + 'x}'
    if type(value) is str:
        return str(byte_format.format(int(value, 0)))
    else:
        return str(byte_format.format(int(value)))


class PacketParser:
    def __init__(self, receive_packet):
        self.message_id = receive_packet[:8]
        self.packet_len = receive_packet[8:16]
        self.client_id = receive_packet[16:20]
        self.session_id = receive_packet[20:24]
        self.protocol_ver = receive_packet[24:26]
        self.interface_ver = receive_packet[26:28]
        self.message_type = receive_packet[28:30]
        self.ret_code = receive_packet[30:32]
        if self.message_id == 'ffff8100':
            self.flags = receive_packet[32:34]
            self.entries_len = receive_packet[40:48]
            self.last_entry_idx = 48 + (int(self.entries_len, 16) * 2)
            if int(self.entries_len, 16) > 0:
                self.entries_array = receive_packet[48:self.last_entry_idx]
                self.entryArray = []
                self.makeEntryList()
            self.options_len = receive_packet[self.last_entry_idx:self.last_entry_idx+8]
            if int(self.options_len, 16) > 0:
                self.options_array = receive_packet[self.last_entry_idx+8:]
                self.optionArray = []
                self.makeOptionList()
        else:
            self.payload = receive_packet[32:]

    def makeEntryList(self):
        entry_count = int(int(self.entries_len, 16) / 16)
        for i in range(entry_count):
            self.entryArray.append(self.entries_array[i*32:i*32+32])

    def makeOptionList(self):
        temp_opt = self.options_array
        while temp_opt:
            option_length = (int(temp_opt[:4], 16) * 2) + 6
            self.optionArray.append(temp_opt[:option_length])
            temp_opt = temp_opt[option_length:]


class EntryArrayParser:
    def __init__(self, entry):
        self.entry_type = entry[:2]
        self.opt_idx1 = entry[2:4]
        self.opt_idx2 = entry[4:6]
        self.opt_num1 = entry[6:7]
        self.opt_num2 = entry[7:8]
        self.entry_service_id = entry[8:12]
        self.instance_id = entry[12:16]
        self.major_version = entry[16:18]
        self.ttl = entry[18:24]
        if self.entry_type == ENTRY_TYPE["FIND"] or self.entry_type == ENTRY_TYPE["OFFER"]:
            self.minor_version = entry[24:]
        elif self.entry_type == ENTRY_TYPE["SUBSCRIBE"] or self.entry_type == ENTRY_TYPE["SUBSCRIBE_ACK"]:
            self.init_flag = entry[26:27]
            self.counter = entry[27:28]
            self.event_group_id = entry[28:]


class OptionArrayParser:
    def __init__(self, option):
        self.length = option[:4]
        self.option_type = option[4:6]
        if self.option_type == OPT_TYPE["Configuration"]:
            self.conf_str = option[8:]
        elif self.option_type == OPT_TYPE["LoadBalancing"]:
            self.priority = option[8:12]
            self.weight = option[12:16]
        elif self.option_type[-1] == '4':
            self.ip_address = option[8:16]
            self.protocol = option[18:20]
            self.port_number = option[20:24]
        elif self.option_type[-1] == '6':
            self.ip_address = option[8:40]
            self.protocol = option[42:44]
            self.port_number = option[44:48]


class SOMEIPPacketGenerator:
    PROTOCOL_VERSION = '01'

    def __init__(self, service_id, method_id, client_id, interface_version):
        self.service_id = valueToByteString(service_id, 2)
        self.method_id = valueToByteString(method_id, 2)
        self.client_id = valueToByteString(client_id, 2)
        if not hasattr(self, 'session_id'):
            self.session_id = '0000'
        self.interface_version = valueToByteString(interface_version, 1)

        self.payload = ''
        self.someip_header = ''

        # someip-sd resource
        self.entry_list = []
        self.option_list = []

    def increaseSessionId(self):
        if self.session_id == 'ffff':
            self.session_id = '0000'
        current_session_id = self.session_id = int(self.session_id, 16) + 1
        self.session_id = valueToByteString(self.session_id, 2)
        return current_session_id

    def someipHeaderBind(self, payload, message_type, ret_code):
        self.payload = payload
        header_length = valueToByteString(int(len(self.payload) / 2) + 8, 4)
        self.someip_header = (
                self.service_id
                + self.method_id
                + header_length
                + self.client_id
                + self.session_id
                + self.PROTOCOL_VERSION
                + self.interface_version
                + MESSAGE_TYPE[message_type]
                + RETURN_CODE[ret_code])

    def sendSomeipMessage(self, sock, dst_address, dst_port):
        sock.sendto(binascii.unhexlify(self.someip_header + self.payload), (dst_address, dst_port))

    def receiveSomeipMessage(self, sock):
        sock.settimeout(10)
        receive_packet, addr = sock.recvfrom(1024)
        return receive_packet.hex(), addr


class SDPacketGenerator(SOMEIPPacketGenerator):
    def __new__(cls, service_id, method_id, client_id, interface_version):
        if not hasattr(cls, 'single_instance'):
            cls.single_instance = super(SDPacketGenerator, cls).__new__(cls)
            cls.session_id = '0000'
        return cls.single_instance

    def addEndpointOption(self, protocol, port, opt_type, ip_address):
        port = valueToByteString(port, 2)
        idx = len(self.option_list)
        if opt_type != "Configuration":
            new_opt = (OPT_LENGTH[opt_type] + OPT_TYPE[opt_type] + RESERVED + ip_address +
                       RESERVED + L4PROTOCOL[protocol] + port)
        else:
            # TODO: Configuration type OPT_LENGTH 설정
            new_opt = None

        if new_opt not in self.option_list:
            self.option_list.append(new_opt)
        else:
            idx = self.option_list.index(new_opt)

        return idx

    def getOptionSize(self):
        option_legnth = 0
        for opt in self.option_list:
            option_legnth += len(opt)
        return valueToByteString(option_legnth/2, 4)

    def makeSDOption(self):
        options = ''
        for opt in self.option_list:
            options += opt
        return options

    def addServiceEntry(self, entry_type, index1, index2, entry_service_id, instance_id, major_version,
                        ttl, minor_version):
        index1 = valueToByteString(index1, 1)
        index2 = valueToByteString(index2, 1)
        entry_service_id = valueToByteString(entry_service_id, 2)
        # TODO : 다중 option 처리
        num_opt1 = valueToByteString(len(self.option_list), 0.5)
        num_opt2 = '0'
        instance_id = valueToByteString(instance_id, 2)
        major_version = valueToByteString(major_version, 1)
        ttl = valueToByteString(ttl, 3)
        minor_version = valueToByteString(minor_version, 4)

        new_entry = ((ENTRY_TYPE[entry_type] + index1 + index2 + num_opt1 + num_opt2 + entry_service_id
                                + instance_id + major_version + ttl + minor_version))

        if new_entry not in self.entry_list:
            self.entry_list.append(new_entry)

    def addEventGroupEntry(self, entry_type, index1, index2, entry_service_id, instance_id, major_version,
                           ttl, event_group_id):
        index1 = valueToByteString(index1, 1)
        index2 = valueToByteString(index2, 1)
        entry_service_id = valueToByteString(entry_service_id, 2)
        num_opt1 = valueToByteString(len(self.option_list), 0.5)
        num_opt2 = '0'
        instance_id = valueToByteString(instance_id, 2)
        major_version = valueToByteString(major_version, 1)
        ttl = valueToByteString(ttl, 3)
        event_group_id = valueToByteString(event_group_id, 2)

        # TODO: initial flag temporary set to RESERVED
        self.entry_list.append((ENTRY_TYPE[entry_type] + index1 + index2 + num_opt1 + num_opt2 + entry_service_id
                                + instance_id + major_version + ttl + RESERVED + RESERVED + event_group_id))

    def getEntrySize(self):
        entry_length = 0
        for entry in self.entry_list:
            entry_length += len(entry)
        return valueToByteString(entry_length/2, 4)

    def makeEntry(self):
        entries = ''
        for entry in self.entry_list:
            entries += entry
        return entries
