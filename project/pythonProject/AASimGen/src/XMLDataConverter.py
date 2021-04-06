'''
Created on Mar 27, 2018

@author: viseng
'''
import logging
from util import order, wraplist, switchmachine

ETH_SPEED_100MBIT = int(1e8)
ETH_SPEED_1GBIT = int(1e9)


class XMLDataConverter:

    def __init__(self, dataElements):
        self.data = dataElements


    def setArgs(self, args):
        self.args = args

    def getProject(self):
        projectName = "FBX4_Vector_" + self.args.project_name
        return order(['@ho:OID', '@ID', 'ho:SHORT-NAME', 'ho:LONG-NAME'], {
            '@ho:OID': projectName,
            '@ID': projectName,
            'ho:SHORT-NAME': projectName,
            'ho:LONG-NAME': {
                '@xml:lang': "en",
                '#text': "FIBEX4 file created by AA2CFBX converter."
            }
        })

    def getNetworkClusters(self):
        clusters = {
            'fx:CLUSTER': []
        }


        self.data['channel_ref'] = []

        for cl_ns, cluster in self.data['ethernetCluster']['values']:

            channels = wraplist(cluster['ETHERNET-CLUSTER-VARIANTS']['ETHERNET-CLUSTER-CONDITIONAL']['PHYSICAL-CHANNELS']['ETHERNET-PHYSICAL-CHANNEL'])

            channel_refs = []
            for channel in channels:
                ref = self._getId(cl_ns, cluster) + "_" + channel['SHORT-NAME']
                channel_refs.append({ '@ID-REF': ref })
                self.data['channel_ref'].append((ref, channel))

            clusters['fx:CLUSTER'].append(order(['@ID', '@xsi:type', 'ho:SHORT-NAME', 'fx:SPEED', 'fx:IS-HIGH-LOW-BIT-ORDER', 'fx:BIT-COUNTING-POLICY', 'fx:PROTOCOL', 'fx:PHYSICAL', 'fx:CHANNEL-REFS', 'fx:MAX-FRAME-LENGTH', 'ethernet:MAC-MULTICAST-GROUPS'], {

                '@xsi:type': "ethernet:CLUSTER-TYPE",
                '@ID': cluster['SHORT-NAME'],
                'ho:SHORT-NAME': cluster['SHORT-NAME'],
                'fx:SPEED': ETH_SPEED_1GBIT,
                'fx:IS-HIGH-LOW-BIT-ORDER': str(True).lower(),
                'fx:BIT-COUNTING-POLICY': 'SAWTOOTH',
                'fx:PROTOCOL': 'ETHERNET',
                'fx:PHYSICAL': 'OABR',
                'fx:CHANNEL-REFS': {
                    'fx:CHANNEL-REF': channel_refs
                },
                'fx:MAX-FRAME-LENGTH': 1500,
                'ethernet:MAC-MULTICAST-GROUPS': {
                    'ethernet:MAC-MULTICAST-GROUP': [order(['ho:SHORT-NAME', 'ethernet:MAC-MULTICAST-ADDRESS'], {
                            '@ID':  cluster['SHORT-NAME'] + '_MACMULTICASTGROUP_SD_1',
                            'ho:SHORT-NAME': 'SD',
                            'ethernet:MAC-MULTICAST-ADDRESS': '33:33:00:00:00:01'
                        }),
                        order(['ho:SHORT-NAME', 'ethernet:MAC-MULTICAST-ADDRESS'], {
                            '@ID': cluster['SHORT-NAME'] + '_MACMULTICASTGROUP_BROADCAST_1',
                            'ho:SHORT-NAME': 'BROADCAST',
                            'ethernet:MAC-MULTICAST-ADDRESS': 'FF:FF:FF:FF:FF:FF'
                        })
                    ]
                }
            }))

        return clusters

    def getChannels(self):
        assert 'channel_ref' in self.data.keys() and "Dev-Error: getNetworkClusters has to be called first!"

        channels = {
            'fx:CHANNEL': []
        }

        for channel_ref, channel in self.data['channel_ref']:
            channels['fx:CHANNEL'].append(order(['@ID', '@xsi:type'], {
                '@xsi:type': "ethernet:CHANNEL-TYPE",
                '@ID': channel_ref,
                'ho:SHORT-NAME': channel['SHORT-NAME']

            }))

            if 'VLAN' in channel.keys():
                channels['fx:CHANNEL'][-1]['ethernet:VIRTUAL-LAN'] = order(['ho:SHORT-NAME', 'ethernet:VLAN-IDENTIFIER'], {
                    '@ID': channel_ref + '_' + channel['VLAN']['SHORT-NAME'],
                    'ho:SHORT-NAME': channel['VLAN']['SHORT-NAME'],
                    'ethernet:VLAN-IDENTIFIER': channel['VLAN']['VLAN-IDENTIFIER']
                })

        return channels

    def _getPath(self, ns, obj):
        return "/" + "/".join(ns + [obj['SHORT-NAME']])

    def _getId(self, ns, obj):
        return self._refToId(self._getPath(ns, obj))

    def getServiceInterfaces(self):
        interfaces = {
            'fx:SERVICE-INTERFACE': []
        }

        self.data['interface_ref'] = []
        self.data['eventGroups'] = {}

        for si_ns, interface in self.data['serviceInterfaces']['values']:
            # find service interface deployment
            depl = None
            if_path = self._getPath(si_ns, interface)
            for _deploy_ns, deployment in self.data['someIpDeployments']['values']:
                if deployment['SERVICE-INTERFACE-REF']['#text'] == if_path:
                    depl = deployment
                    break

            if depl is None:
                raise Exception("ARXML-Error: No deployment found for SI: %s" % (interface['SHORT-NAME']))

            interface_ref = self._getId(si_ns, interface)
            self.data['interface_ref'].append(interface_ref)

            interfaces['fx:SERVICE-INTERFACE'].append(order(['@ID', '@xsi:type', 'ho:SHORT-NAME', 'fx:SERVICE-IDENTIFIER', 'service:API-VERSION', 'service:METHODS', 'service:FIELDS', 'service:EVENT-GROUPS', 'service:MODIFIERS'], {
                '@xsi:type': "service:SERVICE-INTERFACE-TYPE",
                '@ID': interface_ref,
                'ho:SHORT-NAME': interface['SHORT-NAME'],
                'fx:SERVICE-IDENTIFIER': depl['SERVICE-INTERFACE-ID'],
                'service:API-VERSION': order(['service:MAJOR', 'service:MINOR'], {
                    'service:MAJOR': depl['SERVICE-INTERFACE-VERSION']['MAJOR-VERSION'],
                    'service:MINOR': depl['SERVICE-INTERFACE-VERSION']['MINOR-VERSION'],
                }),
                'service:METHODS': {
                    'service:METHOD': self._getMethods(si_ns, interface, _deploy_ns, deployment, interface_ref),
                },
                'service:FIELDS': self._getFields(si_ns, interface, _deploy_ns, deployment, interface_ref),
                'service:EVENT-GROUPS': {},
                'service:MODIFIERS': {
                    'service:MODIFIER': 'PUBLIC'
                }
            }))

            if not len(interfaces['fx:SERVICE-INTERFACE'][-1]['service:METHODS']['service:METHOD']):
                del interfaces['fx:SERVICE-INTERFACE'][-1]['service:METHODS']

            if len(self.data['eventGroups']):
                interfaces['fx:SERVICE-INTERFACE'][-1]['service:EVENT-GROUPS'] = {
                    'service:EVENT-GROUP': self.data['eventGroups'][interface_ref]
                }

        return interfaces


    def _getMethods(self, si_ns, interface, _deploy_ns, deployment, interface_ref):
        methods = []

        if not 'METHODS' in interface.keys():
            return methods
        if interface['METHODS'] is None:
            return methods
        if not 'CLIENT-SERVER-OPERATION' in interface['METHODS'].keys():
            return methods

        for method in wraplist(interface['METHODS']['CLIENT-SERVER-OPERATION']):

            depl = None
            method_path = self._getPath(si_ns, interface) + "/" + method['SHORT-NAME']
            for depl_field in wraplist(deployment['METHOD-DEPLOYMENTS']['SOMEIP-METHOD-DEPLOYMENT']):
                if depl_field['METHOD-REF']['#text'] == method_path:
                    depl = depl_field
                    break

            if depl is None:
                raise Exception("ARXML-Error: No deployment found for METHOD: %s" % (method['SHORT-NAME']))
            method_ref = interface_ref + "_" + method['SHORT-NAME']
            output_parameters = self._getMethodOutputParameters(method, method_ref)
            methods.append(order(['ho:SHORT-NAME', 'service:METHOD-IDENTIFIER', 'service:CALL-SEMANTIC', 'service:INPUT-PARAMETERS', 'service:INPUT-PARAMETERS', 'service:RETURN-PARAMETERS', 'service:RELIABLE'], {
                '@ID': method_ref,
                'ho:SHORT-NAME': method['SHORT-NAME'],
                'service:METHOD-IDENTIFIER':  depl['METHOD-ID'],
                'service:CALL-SEMANTIC': 'SYNCHRONOUS' if len(output_parameters) else 'FIRE_AND_FORGET',
                'service:INPUT-PARAMETERS': {
                    'service:INPUT-PARAMETER': self._getMethodInputParameters(method, method_ref)
                },
                'service:RETURN-PARAMETERS': {
                    'service:RETURN-PARAMETER': output_parameters
                },
                'service:RELIABLE': str(depl['TRANSPORT-PROTOCOL'] == "TCP").lower(),
                'service:SERVICE-TIMING': {
                    'service:METHOD-TIMING': order(['service:REQUEST-DEBOUNCE-TIME-RANGE', 'service:RESPONSE-DEBOUNCE-TIME-RANGE', 'service:MAXIMUM-WAIT-TIME-FOR-RESPONSE'], {
                        'service:REQUEST-DEBOUNCE-TIME-RANGE': 'P0Y0M0DT0H0M0.0S',
                        'service:RESPONSE-DEBOUNCE-TIME-RANGE': 'P0Y0M0DT0H0M0.0S',
                        'service:MAXIMUM-WAIT-TIME-FOR-RESPONSE': 'P0Y0M0DT0H0M0S'
                    })
                },
            }))

        return methods

    def _getMethodInputParameters(self, method, method_ref):
        input_parameters = []

        position = 0
        mandatory = True
        for param in method['ARGUMENTS']['ARGUMENT-DATA-PROTOTYPE']:
            if param['DIRECTION'] == 'IN':
                input_parameters.append(order(['ho:SHORT-NAME', 'fx:DATATYPE-REF', 'service:POSITION', 'service:MANDATORY', 'service:TAG'], {  # DATA-ID
                    '@ID': method_ref + '_' + param['SHORT-NAME'],
                    'ho:SHORT-NAME': param['SHORT-NAME'],
                    'fx:DATATYPE-REF': { '@ID-REF': self._refToId(param['TYPE-TREF']['#text'])},
                    'service:POSITION': position,
                    'service:MANDATORY': str(mandatory).lower(),
                    'service:TAG': position
                }))
                position += 1

        return input_parameters

    def _getMethodOutputParameters(self, method, method_ref):
        output_parameters = []

        position = 0
        mandatory = True
        for param in method['ARGUMENTS']['ARGUMENT-DATA-PROTOTYPE']:
            if param['DIRECTION'] == 'OUT':
                output_parameters.append(order(['ho:SHORT-NAME', 'fx:DATATYPE-REF', 'service:POSITION', 'service:MANDATORY', 'service:TAG'], {  # #DATA-ID
                    '@ID': method_ref + '_' + param['SHORT-NAME'],
                    'ho:SHORT-NAME': param['SHORT-NAME'],
                    'fx:DATATYPE-REF': { '@ID-REF': self._refToId(param['TYPE-TREF']['#text'])},
                    'service:POSITION': position,
                    'service:MANDATORY': str(mandatory).lower(),
                    'service:TAG': position  # #DATA-ID
                }))
                position += 1

        return output_parameters



    def _getFields(self, si_ns, interface, _deploy_ns, deployment, interface_ref):
        fields = {
            'service:FIELD': []
        }

        for field in wraplist(interface['FIELDS']['FIELD']):
            access = self._getFieldAccess(field)

            depl = None
            field_path = self._getPath(si_ns, interface) + "/" + field['SHORT-NAME']
            for depl_field in wraplist(deployment['FIELD-DEPLOYMENTS']['SOMEIP-FIELD-DEPLOYMENT']):
                if depl_field['FIELD-REF']['#text'] == field_path:
                    depl = depl_field
                    break

            if depl is None:
                raise Exception("ARXML-Error: No deployment found for FIELD: %s" % (field['SHORT-NAME']))

            field_ref = interface_ref + "_" + field['SHORT-NAME']
            fields['service:FIELD'].append(order(['ho:SHORT-NAME', 'fx:DATATYPE-REF', 'service:ACCESS-PERMISSION'], {
                '@ID': field_ref,
                'ho:SHORT-NAME': field['SHORT-NAME'],
                'fx:DATATYPE-REF': { '@ID-REF': self._refToId(field['TYPE-TREF']['#text']) },
                'service:ACCESS-PERMISSION': access,
            }))

            if field['HAS-GETTER'] == "true":
                fields['service:FIELD'][-1]['service:GETTER'] = order(['service:METHOD-IDENTIFIER', 'service:RELIABLE'], {
                    'service:METHOD-IDENTIFIER': depl['GET']['METHOD-ID'],
                    'service:RELIABLE': str(depl['GET']['TRANSPORT-PROTOCOL'] == "tcp").lower()
                })
            if field['HAS-SETTER'] == "true":
                fields['service:FIELD'][-1]['service:SETTER'] = order(['service:METHOD-IDENTIFIER', 'service:RELIABLE'], {
                    'service:METHOD-IDENTIFIER': depl['SET']['METHOD-ID'],
                    'service:RELIABLE': str(depl['SET']['TRANSPORT-PROTOCOL'] == "tcp").lower()
                })
            if field['HAS-NOTIFIER'] == "true":
                fields['service:FIELD'][-1]['service:NOTIFIER'] = order(['service:NOTIFICATION-IDENTIFIER', 'service:RELIABLE'], {
                    'service:NOTIFICATION-IDENTIFIER': depl['NOTIFIER']['EVENT-ID'],
                    'service:RELIABLE': str(depl['NOTIFIER']['TRANSPORT-PROTOCOL'] == "tcp").lower()
                })

            # add eventgroup for each notifier

            # find event group in deployment
            evtgrp_depl = None
            notifier_path = self._getPath(_deploy_ns, deployment) + "/" + field['SHORT-NAME'] + "/" + depl['NOTIFIER']['SHORT-NAME']
            for depl_evtgrp in wraplist(deployment['EVENT-GROUPS']['SOMEIP-EVENT-GROUP']):
                if depl_evtgrp['EVENT-REFS']['EVENT-REF']['#text'] == notifier_path:
                    evtgrp_depl = depl_evtgrp
                    break

            if evtgrp_depl is None:
                raise Exception("ARXML-Error: No EVENT deployment found for FIELD NOTIFIER: %s" % (depl['NOTIFIER']['SHORT-NAME']))

            eventrgroupd_id = self._getId(_deploy_ns, deployment) + "_" + depl_evtgrp['SHORT-NAME']
            if interface_ref not in self.data['eventGroups'].keys():
                self.data['eventGroups'][interface_ref] = []

            self.data['eventGroups'][interface_ref].append(order(['ho:SHORT-NAME', 'fx:SERVICE-IDENTIFIER', 'service:FIELD-REFS'], {
                '@ID': eventrgroupd_id,  # interface_ref + "_" + field['SHORT-NAME'] + "_EVENTGROUP",
                'ho:SHORT-NAME':  interface['SHORT-NAME'] + "_" + field['SHORT-NAME'] + "SomeipEventGroup",
                'fx:SERVICE-IDENTIFIER': evtgrp_depl['EVENT-GROUP-ID'],
                'service:FIELD-REFS': {
                    'service:FIELD-REF': {
                        '@ID-REF': field_ref
                    }
                }
            }))

        return fields


    def _getFieldAccess(self, field):
        try:
            notifier = field['HAS-NOTIFIER'] == "true"
        except:
            whoops = []
        getter = field['HAS-GETTER'] == "true"
        setter = field['HAS-SETTER'] == "true"
        access = []

        if notifier:
            access.append("NOTIFY")

        if getter:
            access.append("READ")
        if setter:
            access.append("WRITE")
        if not (getter and setter):
            access.append("ONLY")

        return "_".join(access)


    def _refToId(self, ref):
        return ref[1:].replace("/", "_")


    def getDatatypes(self):
        datatypes = []
        obj = {
            'fx:DATATYPE': datatypes
        }

        # just saw that this is not needed ATM, so far skipping!
        # at first, appPrimitiveDatatypes, that are enumerations
#         enumerations = self._getEnumerations()
#         if len(enumerations):
#             datatypes.extend(enumerations)

        implementationDatatypes = self._getImplDatatypes()
        if len(implementationDatatypes):
            datatypes.extend(implementationDatatypes)

        return obj

    def _getSimpleDatatype(self, ns, name, dtsize=0, isStringType=False):
        type_id = "_".join(ns) + "_" + name
        coding_id = "_".join(ns) + "_" + name + '_coding'

        self.data['coding_ids'][name] = coding_id

        datatype = order(['@ID', '@xsi:type', 'ho:SHORT-NAME', 'fx:CODING-REF'], {
            '@xsi:type': 'fx:COMMON-DATATYPE-TYPE',
            '@ID': type_id,
            'ho:SHORT-NAME': name,
            'fx:CODING-REF': {
                '@ID-REF': coding_id
            }
        })

        # add coding, maybe byte-order swBaseType['BYTE-ORDER'] gets relevant some time
        self.data['codings'].append(order(['ho:SHORT-NAME', 'ho:CODED-TYPE'], {
            '@ID': coding_id,
            'ho:SHORT-NAME': name,
            'ho:CODED-TYPE': order(['@ho:BASE-DATA-TYPE', '@CATEGORY'], {
                '@ho:BASE-DATA-TYPE': self._getBaseDataType(name),
                '@CATEGORY': 'STANDARD-LENGTH-TYPE'
            })
        }))

        if isStringType:
            self.data['codings'][-1]['ho:CODED-TYPE']['@CATEGORY'] = 'LEADING-LENGTH-INFO-TYPE'
            self.data['codings'][-1]['ho:CODED-TYPE']['@ENCODING'] = 'UTF-8'
            self.data['codings'][-1]['ho:CODED-TYPE']['@TERMINATION'] = 'ZERO'
            self.data['codings'][-1]['ho:CODED-TYPE']['@BYTE-ORDER-MARK'] = 'NONE'
            self.data['codings'][-1]['ho:CODED-TYPE']['ho:MIN-LENGTH'] = dtsize
        else:
            self.data['codings'][-1]['ho:CODED-TYPE']['ho:BIT-LENGTH'] = dtsize

        return datatype

    def _getBaseDataType(self, name):
        bdt = "A_"
        if name.lower() == "string":
            bdt += "UNICODE2STRING"
        elif name.lower() == "float":
            bdt += "float32"
        elif name.lower() == "double":
            bdt += "float64"
        elif name.lower() == "boolean":
            bdt += "uint8"
        elif 'sint' in name:
            bdt += name.replace('sint', 'int')
        else:
            bdt += name
        return bdt.upper()

    def _getImplDatatypes(self):

        self.data['codings'] = []
        self.data['coding_ids'] = {}

        listOfDataTypes = []

        for idt_ns, implDatatype in self.data['implementationDatatypes']['values']:

            # check category of datatype
            if implDatatype['CATEGORY'] == "STRING":  # similar to SW-BASE-TYPE
                listOfDataTypes.append(self._getSimpleDatatype(idt_ns, implDatatype['SHORT-NAME'], isStringType=True))

            elif implDatatype['CATEGORY'] == "TYPE_REFERENCE":
                conds = implDatatype['SW-DATA-DEF-PROPS']['SW-DATA-DEF-PROPS-VARIANTS']['SW-DATA-DEF-PROPS-CONDITIONAL']

                datatype_ref = None
                if isinstance(conds, list):
                    # ok, search for IMPLEMENTATION-DATA-TYPE-REF
                    for cond in conds:
                        if 'IMPLEMENTATION-DATA-TYPE-REF' in cond.keys():
                            datatype_ref = cond['IMPLEMENTATION-DATA-TYPE-REF']['#text']

                if datatype_ref is None:
                    raise Exception("ARXML-Error: No type for referenced datatpye in Implpementation-Datatype %s found", implDatatype['SHORT-NAME'])

                type_id = "_".join(idt_ns) + "_" + implDatatype['SHORT-NAME']
                listOfDataTypes.append(order(['@ID', '@xsi:type', 'ho:SHORT-NAME', 'fx:CODING-REF'], {
                    '@xsi:type': 'fx:COMMON-DATATYPE-TYPE',
                    '@ID': type_id,
                    'ho:SHORT-NAME': implDatatype['SHORT-NAME'],
                    'fx:CODING-REF': {
                        '@ID-REF': self._refToId(datatype_ref) + '_coding'
                    }
                }))

#
#                 listOfDataTypes.append(order(['ho:SHORT-NAME', 'fx:DATATYPE-REF', 'fx:COMPLEX-DATATYPE-CLASS'], {
#                     '@xsi:type': 'fx:COMPLEX-DATATYPE-TYPE',
#                     '@ID': type_id,
#                     'ho:SHORT-NAME': implDatatype['SHORT-NAME'],
#                     'fx:DATATYPE-REF': { '@ID-REF': self._refToId(datatype_ref) },
#                     'fx:COMPLEX-DATATYPE-CLASS': 'TYPEDEF',
#                 }))



            elif implDatatype['CATEGORY'] == "STRUCTURE":
                type_id = "_".join(idt_ns) + "_" + implDatatype['SHORT-NAME']

                listOfDataTypes.append(order(['@ID', '@xsi:type', 'ho:SHORT-NAME', 'fx:COMPLEX-DATATYPE-CLASS', 'fx:MEMBERS'], {
                    '@xsi:type': 'fx:COMPLEX-DATATYPE-TYPE',
                    '@ID': type_id,
                    'ho:SHORT-NAME': implDatatype['SHORT-NAME'],
                    'fx:COMPLEX-DATATYPE-CLASS': 'STRUCTURE',
                    'fx:MEMBERS': {
                        'fx:MEMBER': self._getStructMembers(idt_ns, implDatatype, type_id)
                    }
                }))

            elif  implDatatype['CATEGORY'] == "VECTOR" or \
                  implDatatype['CATEGORY'] == "ARRAY"  :
                type_id = "_".join(idt_ns) + "_" + implDatatype['SHORT-NAME']

                datatype = order(['@ID', '@xsi:type', 'ho:SHORT-NAME', 'fx:COMPLEX-DATATYPE-CLASS', 'fx:MEMBERS'], {
                    '@xsi:type': 'fx:COMPLEX-DATATYPE-TYPE',
                    '@ID': type_id,
                    'ho:SHORT-NAME': implDatatype['SHORT-NAME'],
                    'fx:COMPLEX-DATATYPE-CLASS': 'TYPEDEF',
                    'fx:MEMBERS': {
                        'fx:MEMBER': self._getArrayMembers(idt_ns, implDatatype, type_id),
                    },
                })

                listOfDataTypes.append(datatype)

                pass
            elif  implDatatype['CATEGORY'] == "VALUE":
                # find corresponding type reference in SW-BASE-TYPES
                ref = implDatatype['SW-DATA-DEF-PROPS']['SW-DATA-DEF-PROPS-VARIANTS']['SW-DATA-DEF-PROPS-CONDITIONAL']['BASE-TYPE-REF']
                if ref['@DEST'] != "SW-BASE-TYPE":
                    raise Exception("ARXML-Error: Only SW-BASE-TYPE refs supported for Implpementation-Datatypes with CATEGORY = VALUE")
                sbt_ref = None
                for sbt_ns, swBaseType in self.data['swBaseTypes']['values']:
                    sbt_path = self._getPath(sbt_ns, swBaseType)
                    if sbt_path == ref["#text"]:
                        sbt_ref = swBaseType
                        break

                if sbt_ref is None:
                    raise Exception("ARXML-Error: No SW-BASE-TYPE found for IMPL-DATATYPE: %s" % (implDatatype['SHORT-NAME']))

                # careful: use ns of impl-datatype and name of impl-type, only size from swbt!
                listOfDataTypes.append(self._getSimpleDatatype(idt_ns, implDatatype['SHORT-NAME'], sbt_ref['BASE-TYPE-SIZE']))



            else:

                logging.warning("Development-Warning: Unhandled datatype category type: %s", implDatatype['CATEGORY'])

        return listOfDataTypes


    def getCodings(self):
        assert 'codings' in self.data.keys() and "Dev-Error: _getSwBaseTypes has to be called first!"
        return {
            'fx:CODING': self.data['codings']
        }


    def _getStructMembers(self, ns, datatype, type_id):
        members = []
        index = 0
        datatype_ref = self._getPath(ns, datatype)

        for member in wraplist(datatype['SUB-ELEMENTS']['IMPLEMENTATION-DATA-TYPE-ELEMENT']):
            if member['CATEGORY'] == 'TYPE_REFERENCE':
                if member['SW-DATA-DEF-PROPS']['SW-DATA-DEF-PROPS-VARIANTS']['SW-DATA-DEF-PROPS-CONDITIONAL']['IMPLEMENTATION-DATA-TYPE-REF']['@DEST'] != 'IMPLEMENTATION-DATA-TYPE':
                    raise Exception("ARXML-Error: Not supported sub element datatype-ref type %s for datatype: %s, member %s" % (member['SW-DATA-DEF-PROPS']['SW-DATA-DEF-PROPS-VARIANTS']['SW-DATA-DEF-PROPS-CONDITIONAL']['IMPLEMENTATION-DATA-TYPE-REF']['@DEST'], datatype['SHORT-NAME'], member['SHORT-NAME']))

                # This is really simplified lookup for sif to be used by TLV options
                # FIBEX would need several datatypes for a datatype that is used in different interfaces with different TLV settings
                # VW use-case is: one datatype only used by one interface with the same TLV settings
                sif = None
                mandatory = True
                member_ref = datatype_ref + "/" + member['SHORT-NAME']
                root_prot_ref = None
                for _sif_ns, sif in self.data['serviceInterfaces']['values']:
                    for optional in sif['OPTIONAL-ELEMENTS']['SERVICE-INTERFACE-SUB-ELEMENT']['OPT-IMPL-RECORD-ELEMENTS']['IMPLEMENTATION-DATA-TYPE-ELEMENT-IN-AUTOSAR-DATA-PROTOTYPE-REF']:
                        ctxDataTypeRefs = optional['CONTEXT-DATA-PROTOTYPE-REFS']['CONTEXT-DATA-PROTOTYPE-REF']
                        if isinstance(ctxDataTypeRefs, list):
                            raise Exception("ARXML-Error: Not more then one reference allowed for optional elements in %s" % (sif['SHORT-NAME']))

                        if member_ref == optional['TARGET-DATA-PROTOTYPE-REF']['#text']:
                            mandatory = False
                            root_prot_ref = optional['ROOT-AUTOSAR-DATA-PROTOTYPE-REF']['#text']

                # find corresponding TLV configuration in someip transformation properties
                tlv_dataid = None
                for _transpropns_ns, transprop in self.data['someIpTransformerProps']['values']:
                    compoDataProtRefs = transprop['DATA-PROTOTYPES']['COMPOSITION-DATA-PROTOTYPE-REF']
                    if isinstance(compoDataProtRefs, dict):
                        compoDataProtRefs = [compoDataProtRefs]

                    for compoDataProtRef in compoDataProtRefs:
                        if compoDataProtRef['DATA-PROTOTYPE-IREF']['TARGET-DATA-PROTOTYPE-REF']['#text'] == root_prot_ref and \
                           compoDataProtRef['ELEMENT-IN-IMPL-DATATYPE']['TARGET-DATA-PROTOTYPE-REF']['#text'] == member_ref:
                            tlv_dataid = compoDataProtRef['TLV-DATA-ID']

                if tlv_dataid is None and mandatory is False:
                    raise Exception("ARXML-Error: No data-id for the element %s in datatype %s given" % (member['SHORT-NAME'], datatype['SHORT-NAME']))

                member_type_id = self._refToId(member['SW-DATA-DEF-PROPS']['SW-DATA-DEF-PROPS-VARIANTS']['SW-DATA-DEF-PROPS-CONDITIONAL']['IMPLEMENTATION-DATA-TYPE-REF']['#text'])
                members.append(order(['ho:SHORT-NAME', 'fx:DATATYPE-REF', 'fx:POSITION'], {  # , , 'fx:MANDATORY'
                    '@ID': type_id + "_" + member['SHORT-NAME'] + '_member',
                    'ho:SHORT-NAME': member['SHORT-NAME'],
                    'fx:DATATYPE-REF': {
                        '@ID-REF': member_type_id  # datatype_ref)
                    },
                    'fx:POSITION': index,
                }))
                if tlv_dataid is not None:
                    members[-1]['fx:MANDATORY'] = str(mandatory).lower()
                    members[-1]['fx:TAG'] = tlv_dataid  # #DATA-ID


            else:
                raise Exception("ARXML-Error: Not supported sub element %s for datatype: %s" % (member['CATEGORY'], datatype['SHORT-NAME']))
            index += 1

        return members

    def _getArrayMembers(self, ns, datatype, type_id):
        members = []
        index = 0
        member = datatype['SUB-ELEMENTS']['IMPLEMENTATION-DATA-TYPE-ELEMENT']
        if isinstance(member, list):
            raise Exception("ARXML-Error: Array must have exact one member. Datatype: %s" % (datatype['SHORT-NAME']))

        if member['CATEGORY'] == 'TYPE_REFERENCE':
            if member['SW-DATA-DEF-PROPS']['SW-DATA-DEF-PROPS-VARIANTS']['SW-DATA-DEF-PROPS-CONDITIONAL']['IMPLEMENTATION-DATA-TYPE-REF']['@DEST'] != 'IMPLEMENTATION-DATA-TYPE':
                raise Exception("ARXML-Error: Not supported sub element datatype-ref type %s for datatype: %s, member %s" % (member['SW-DATA-DEF-PROPS']['SW-DATA-DEF-PROPS-VARIANTS']['SW-DATA-DEF-PROPS-CONDITIONAL']['IMPLEMENTATION-DATA-TYPE-REF']['@DEST'], datatype['SHORT-NAME'], member['SHORT-NAME']))

            # default values for vector:
            minimum_size = 0
            maximum_size = 10

            if 'ARRAY-SIZE-SEMANTICS' in member.keys():
                if member['ARRAY-SIZE-SEMANTICS'] == "FIXED-SIZE":
                    minimum_size = member['ARRAY-SIZE']
                    maximum_size = minimum_size

#             mandatory = True  # TODO: check TLV here /// necessary for array?
            members.append(order(['ho:SHORT-NAME', 'fx:DATATYPE-REF', 'fx:ARRAY-DECLARATION', 'fx:UTILIZATION', 'fx:POSITION'], {
                '@ID': type_id + "_" + member['SHORT-NAME'],
                'ho:SHORT-NAME': member['SHORT-NAME'],
                'fx:DATATYPE-REF': {
                    '@ID-REF': self._refToId(
                        member['SW-DATA-DEF-PROPS']['SW-DATA-DEF-PROPS-VARIANTS']['SW-DATA-DEF-PROPS-CONDITIONAL']['IMPLEMENTATION-DATA-TYPE-REF']['#text']
                    )
                },
                'fx:ARRAY-DECLARATION': {
                    'fx:ARRAY-DIMENSION': order(['fx:DIMENSION', 'fx:MINIMUM-SIZE'], {  # , 'fx:MAXIMUM-SIZE'
                        'fx:DIMENSION': 0,
                        'fx:MINIMUM-SIZE': minimum_size,
                        # 'fx:MAXIMUM-SIZE': maximum_size,
                    })
                },
                'fx:UTILIZATION': {
                    'fx:SERIALIZATION-ATTRIBUTES': order(['fx:LENGTH-FIELD-SIZE', 'fx:ARRAY-LENGTH-FIELD-SIZE'], {
                        'fx:LENGTH-FIELD-SIZE': 32,
                        'fx:ARRAY-LENGTH-FIELD-SIZE': 32,
                    })
                },

                'fx:POSITION': index,
#                 'fx:UTILIZATION': {
#                     'fx:SERIALIZATION-ATTRIBUTES': {
#                     }
#                 }
#                 'fx:MANDATORY': str(mandatory).lower(),
#                 'fx:DATA-ID': index
            }))

            if maximum_size != 0:
                members[-1]['fx:ARRAY-DECLARATION']['fx:ARRAY-DIMENSION']['fx:MAXIMUM-SIZE'] = maximum_size

#                 <fx:UTILIZATION>
#                   <fx:IS-HIGH-LOW-BYTE-ORDER>true</fx:IS-HIGH-LOW-BYTE-ORDER>
#                   <fx:SERIALIZATION-ATTRIBUTES>
#                     <fx:INHERIT>true</fx:INHERIT>
#                     <fx:LENGTH-FIELD-SIZE>16</fx:LENGTH-FIELD-SIZE>
#                   </fx:SERIALIZATION-ATTRIBUTES>
#                 </fx:UTILIZATION>
            # add lenght field for dynamic arrays
#             if minimum_size != maximum_size and minimum_size == 0:
#                 members[-1]['fx:UTILIZATION'] = {
#                     'fx:SERIALIZATION-ATTRIBUTES': {
#                         'fx:ARRAY-LENGTH-FIELD-SIZE': 32,
#                     }
#                 }

        else:
            raise Exception("ARXML-Error: Not supported sub element %s for datatype: %s" % (member['CATEGORY'], datatype['SHORT-NAME']))
        index += 1

        return members


# ENUMs are nice to have feature, @TODO when time is available / really needed

    # saw that this is not needed ATM, so far skipping!
#     def _getEnumerations(self):
#
#         listOfDataTypes = []
#
#         for apd_ns, app_prim_datatype in self.data['appPrimitiveDatatypes']['values']:
#             type_id = "_".join(apd_ns) + "_" + app_prim_datatype['SHORT-NAME']
#             datatype = {
#                 '@xsi:type': 'fx:ENUM-DATATYPE-TYPE',
#                 '@ID': type_id,
#                 'ho:SHORT-NAME': app_prim_datatype['SHORT-NAME'],
#                 'fx:CODING-REF': 'Coding_UINT8', # TODO, this has to be calculated?
#                 'fx:ENUMERATION-ELEMENTS': {
#                     <fx:ENUM-ELEMENT>
#                       <fx:VALUE>0</fx:VALUE>
#                       <fx:SYNONYM>PERFORM_SUMMATORY</fx:SYNONYM>
#                     </fx:ENUM-ELEMENT>
#                     <fx:ENUM-ELEMENT>
#                       <fx:VALUE>1</fx:VALUE>
#                       <fx:SYNONYM>RETURN_MEMORY_ARRANGEMENT</fx:SYNONYM>
#                     </fx:ENUM-ELEMENT>
#                  }
#             }
#
#
#         return listOfDataTypes

# def getCompuMethods():
#             elif  compuMethod['CATEGORY'] == "TEXTTABLE":
#                 pass




    def getEcus(self):

        ecus = []
        obj = {
            'fx:ECU': ecus
        }

        for machine_ns, machine in self.data['machines']['values']:

            ecus.append(order(['ho:SHORT-NAME', 'fx:CONNECTORS'], {
                '@ID': self._getId(machine_ns, machine),
                'ho:SHORT-NAME': machine['SHORT-NAME'],
                'fx:CONNECTORS': {
                    'fx:CONNECTOR': self._getConnectors(machine_ns, machine)
                }
            }))


        return obj


    def _getConnectors(self, machine_ns, machine):
        connectors = []
        comm_conns = machine['COMMUNICATION-CONNECTORS']['ETHERNET-COMMUNICATION-CONNECTOR']
        if not isinstance(comm_conns, list):
            comm_conns = [comm_conns]

        sd_configs = machine['SERVICE-DISCOVER-CONFIGS']['SOMEIP-SERVICE-DISCOVERY']
        if not isinstance(sd_configs, list):
            sd_configs = [sd_configs]

        connectors.extend(comm_conns)
        connectors.extend(sd_configs)

        connectors_by_channel_of_endpoint = {}

        for connector in connectors:
            endpoint_ref = None
            isSdRef = False
            if 'UNICAST-NETWORK-ENDPOINT-REF' in connector.keys():
                endpoint_ref = connector['UNICAST-NETWORK-ENDPOINT-REF']['#text']
            elif 'MULTICAST-SD-IP-ADDRESS-REF' in connector.keys():
                endpoint_ref = connector['MULTICAST-SD-IP-ADDRESS-REF']['#text']
                isSdRef = True

            channel_ref = self._getChannelOfEndpoint(endpoint_ref)

            if not channel_ref in connectors_by_channel_of_endpoint.keys():
                connectors_by_channel_of_endpoint[channel_ref] = {'net_endpoint_refs': [], 'app_endpoint_refs': []}

            connectors_by_channel_of_endpoint[channel_ref]['net_endpoint_refs'].append(
                endpoint_ref
            )

            if isSdRef:
                connectors_by_channel_of_endpoint[channel_ref]['app_endpoint_refs'].append(
                    ('SD', endpoint_ref, {'port': connector['SOMEIP-SERVICE-DISCOVERY-PORT']})
                )

                if 'sd_endpoints' not in self.data.keys():
                    self.data['sd_endpoints'] = {}
                self.data['sd_endpoints'][channel_ref] = (endpoint_ref, self._getNetworkEndpoint(endpoint_ref))

        self._addProvidedConsumedApplicationEndpoints(connectors_by_channel_of_endpoint, machine_ns, machine)

        ret_connectors = []
        for channel_ref, obj in connectors_by_channel_of_endpoint.items():
            net_endpoint_refs = obj['net_endpoint_refs']
            app_endpoint_refs = obj['app_endpoint_refs']
            con_id = self._getId(machine_ns, machine) + "_" + channel_ref.split("/")[-1]
            sd_endpoint = self.data['sd_endpoints'][channel_ref]
            sd_config = sd_endpoint[1]['NETWORK-ENDPOINT-ADDRESSES']['IPV-6-CONFIGURATION']

            ret_connectors.append(order(['@ID', '@xsi:type', 'fx:CHANNEL-REF', 'it:NETWORK-ENDPOINTS', 'it:APPLICATION-ENDPOINTS', 'it:SERVICE-DISCOVERY-CONFIGURATION'], {
                '@xsi:type': 'it:CONNECTOR-TYPE',
                '@ID': con_id,
                'fx:CHANNEL-REF': {
                    '@ID-REF': self._refToId(channel_ref)
                },
                'it:NETWORK-ENDPOINTS': {
                    'it:NETWORK-ENDPOINT': self._getNetworkEndpoints(net_endpoint_refs)
                },
                'it:APPLICATION-ENDPOINTS': {
                    'it:APPLICATION-ENDPOINT': self._getApplicationEndpoints(app_endpoint_refs)
                },

                'it:SERVICE-DISCOVERY-CONFIGURATION': order(['it:SD-MULTICAST-APPLICATION-ENDPOINT', 'it:SD-MULTICAST-ADDRESS'], {
                    'it:SD-MULTICAST-APPLICATION-ENDPOINT': {
                        'it:APPLICATION-ENDPOINT-REF': { '@ID-REF': self._refToId(sd_endpoint[0]) },
                    },
                    'it:SD-MULTICAST-ADDRESS': {
                        'it:IPV6': order(['it:IPV6-ADDRESS', 'it:IP-ADDRESS-PREFIX-LENGTH', 'it:IPV6-ADDRESS-SOURCE'], {
                            'it:IPV6-ADDRESS': sd_config['IPV-6-ADDRESS'],
                            'it:IP-ADDRESS-PREFIX-LENGTH': sd_config['IP-ADDRESS-PREFIX-LENGTH'],
                            'it:IPV6-ADDRESS-SOURCE': sd_config['IPV-6-ADDRESS-SOURCE']
                        })
                    }
                }),
            }))


        return ret_connectors


    def _addProvidedConsumedApplicationEndpoints(self, connectors_by_channel_of_endpoint, machine_ns, machine):

        appl_endpoints = {}

        # it's time to add the provided and consumed application endpoints, based on the service instance to machine mappings
        # this is a bit complex to do and is done for each machine by it's own (see parameter machine).
        #
        for _si2mm_ns, si2mm in self.data['svnInstToMachineMappings']['values']:

            comm_conn_ref = si2mm['COMMUNICATION-CONNECTOR-REF']['#text']
            comm_conns = wraplist(machine['COMMUNICATION-CONNECTORS']['ETHERNET-COMMUNICATION-CONNECTOR'])

            connector = None
            machine_ref = self._getPath(machine_ns, machine)
            for comm_conn in comm_conns:
                if comm_conn_ref == machine_ref + "/" + comm_conn['SHORT-NAME']:
                    connector = comm_conn
                    break

            if connector is None:
                continue  # belongs to other machine
                try:  # TODO: set flag and proove at the end, if everything found then
                    raise Exception("ARXML-Error: No connector found for %s" % (comm_conn_ref))
                except:
                    print("whoosh")

            endpoint_ref = None
            if 'UNICAST-NETWORK-ENDPOINT-REF' in connector.keys():
                endpoint_ref = connector['UNICAST-NETWORK-ENDPOINT-REF']['#text']
            elif 'MULTICAST-SD-IP-ADDRESS-REF' in connector.keys():
                raise Exception("ARXML-Error: No SD endpoint allowed for required/provided interfaces. Specified in %s/%s" % (si2mm['SHORT-NAME'], connector['SHORT-NAME']))

            channel_ref = self._getChannelOfEndpoint(endpoint_ref)

            (ssi_ns, svc_inst, inst_type) = self._getSomeIpInstanceByPath(si2mm['SERVICE-INSTANCE-REF'])

            if svc_inst is None:
                raise Exception("ARXML-Error: No required/provided service instance found  for %s\n%s" % (si2mm['SHORT-NAME']['#text'], si2mm['SERVICE-INSTANCE-REF']['#text']))

            # currently only UDP used
            protocol = 'UDP'
            port = si2mm['UDP-PORT']

            if endpoint_ref not in appl_endpoints.keys():
                appl_endpoints[endpoint_ref] = {'TCP': {}, 'UDP': {}}

            if port not in appl_endpoints[endpoint_ref][protocol].keys():
                appl_endpoints[endpoint_ref][protocol][port] = {'svc_instances': {'PROVIDED': [], 'REQUIRED': []}}

            # check if already existing
#             duplicate = False
#             for existing in appl_endpoints[endpoint_ref][protocol][port]['svc_instances'][inst_type]:
#                 if self._getId(existing[0], existing[1]) == self._getId(ssi_ns, svc_inst):
#                     duplicate = True
#
#             if not duplicate:
            appl_endpoints[endpoint_ref][protocol][port]['svc_instances'][inst_type].append((ssi_ns, svc_inst))


        for endpoint_ref, items_endpoint_ref in appl_endpoints.items():
            for protocol, items_proto in items_endpoint_ref.items():
                for port, items_port in items_proto.items():
                    # to not get consumed interfaces twice in fibex (possible, but needs more work)
                    # remove the consumed interfaces from the list, if they are provided by the same machine
                    to_remove = []
                    for required_interface in items_port['svc_instances']['REQUIRED']:
                        # check if available in provided
                        _a = required_interface
                        for provided_interface in items_port['svc_instances']['PROVIDED']:
                            if required_interface[1]['SERVICE-INTERFACE-REF']['#text'] == \
                               provided_interface[1]['SERVICE-INTERFACE-REF']['#text']:
                                logging.info("Instance %s is provided by same machine, remove consumed interface", self._getPath(required_interface[0], required_interface[1]))
                                to_remove.append(required_interface)
                                break

                    for item in to_remove:
                        items_port['svc_instances']['REQUIRED'].remove(item)

                    connectors_by_channel_of_endpoint[channel_ref]['app_endpoint_refs'].append(('PROVIDED_REQUIRED', endpoint_ref, {
                        'port': port,
                        'protocol': protocol,
                        'svc_instances': items_port['svc_instances']
                    }))

    def _getSomeIpInstanceByPath(self, refObject):
        if refObject['@DEST'] == "PROVIDED-SOMEIP-SERVICE-INSTANCE":
            for provssi_ns, provssi in self.data['providedSomeIpInstances']['values']:
                if self._getPath(provssi_ns, provssi) == refObject['#text']:
                    return provssi_ns, provssi, 'PROVIDED'

        elif refObject['@DEST'] == "REQUIRED-SOMEIP-SERVICE-INSTANCE":
            for reqssi_ns, reqssi in self.data['requiredSomeIpInstances']['values']:
                if self._getPath(reqssi_ns, reqssi) == refObject['#text']:
                    return reqssi_ns, reqssi, 'REQUIRED'


        return None, None, None

#     def _getSomeIpInstanceByInterface(self, refObject):
#         if refObject['@DEST'] == "SOMEIP-SERVICE-INTERFACE-DEPLOYMENT":
#             for provssi_ns, provssi in self.data['providedSomeIpInstances']['values']:
#                 if provssi['SERVICE-INTERFACE-REF']['#text'] == refObject['#text']:
#                     return provssi_ns, provssi, 'PROVIDED'
#
#         elif refObject['@DEST'] == "REQUIRED-SOMEIP-SERVICE-INSTANCE":
#             for reqssi_ns, reqssi in self.data['requiredSomeIpInstances']['values']:
#                 if reqssi['SERVICE-INTERFACE-REF']['#text'] == refObject['#text']:
#                     return reqssi_ns, reqssi, 'REQUIRED'
#
#         return None, None, None



    def _getChannelOfEndpoint(self, endpoint):
        # strip last element off
        return "/".join(endpoint.split("/")[:-1])


    def _getNetworkEndpoints(self, endpoint_refs):
        endpoints = []

        for ref in endpoint_refs:

            endp = self._getNetworkEndpoint(ref)

            endpoints.append({
                '@ID': self._refToId(ref),
                'it:NETWORK-ENDPOINT-ADDRESSES': {
                    'it:NETWORK-ENDPOINT-ADDRESS': {
                        'it:IPV6': order(['it:IPV6-ADDRESS', 'it:IPV6-ADDRESS-SOURCE'], {
                            'it:IPV6-ADDRESS': endp['NETWORK-ENDPOINT-ADDRESSES']['IPV-6-CONFIGURATION']['IPV-6-ADDRESS'],
                            'it:IPV6-ADDRESS-SOURCE': endp['NETWORK-ENDPOINT-ADDRESSES']['IPV-6-CONFIGURATION']['IPV-6-ADDRESS-SOURCE']
                        })
                    }
                }
            })


        return endpoints

    def _getNetworkEndpoint(self, ref):
        endp = None
        for cl_ns, cluster in self.data['ethernetCluster']['values']:
            channels = wraplist(cluster['ETHERNET-CLUSTER-VARIANTS']['ETHERNET-CLUSTER-CONDITIONAL']['PHYSICAL-CHANNELS']['ETHERNET-PHYSICAL-CHANNEL'])
            for channel in channels:
                channel_ref = self._getPath(cl_ns, cluster) + "/" + channel['SHORT-NAME']

                avail_endpoints = channel['NETWORK-ENDPOINTS']['NETWORK-ENDPOINT']
                for endpoint in avail_endpoints:
                    endpoint_ref = channel_ref + "/" + endpoint['SHORT-NAME']
                    if endpoint_ref == ref:
                        endp = endpoint
                        break
        if endp is None:
            raise Exception("ARXML-Error: No endpoint found for ref %s" % (ref))
        return endp


    def _getApplicationEndpoints(self, endpoint_refs):
        endpoints = []

        # endpoint_refs is tuple: type, endpoint_ref, port
        for ep_type, endpoint_ref, options in endpoint_refs:
            if ep_type == 'SD':
                endpoints.append(order(['it:IT-TRANSPORT-PROTOCOL-CONFIGURATION', 'it:NETWORK-ENDPOINT-REF', 'it:DISCOVERY-TECHNOLOGY', 'it:SERIALIZATION-TECHNOLOGY', 'it:REMOTING-TECHNOLOGY'], {
                    '@ID': self._refToId(endpoint_ref + "/" + "AEP_SD"),
                    'it:IT-TRANSPORT-PROTOCOL-CONFIGURATION': {
                        'it:UDP-TP': {
                            'it:UDP-PORT': { 'it:PORT-NUMBER': options['port'] }
                        }
                    },
                    'it:NETWORK-ENDPOINT-REF': { '@ID-REF': self._refToId(endpoint_ref) },
                    'it:DISCOVERY-TECHNOLOGY': order(['it:DISCOVERY-TECHNOLOGY-NAME', 'it:VERSION'], {
                        'it:DISCOVERY-TECHNOLOGY-NAME': 'SOME/IP',
                        'it:VERSION': 1
                    }),
                    'it:SERIALIZATION-TECHNOLOGY': order(['it:SERIALIZATION-TECHNOLOGY-NAME', 'it:VERSION'], {
                        'it:SERIALIZATION-TECHNOLOGY-NAME': 'SOME/IP',
                        'it:VERSION': 1
                    }),
                    'it:REMOTING-TECHNOLOGY': order(['it:REMOTING-TECHNOLOGY-NAME', 'it:VERSION'], {
                        'it:REMOTING-TECHNOLOGY-NAME': 'SOME/IP',
                        'it:VERSION': 1
                    })
                }))

            elif ep_type == "PROVIDED_REQUIRED":
                appl_endpoint_id = self._refToId(endpoint_ref + '/' + 'AEP' + '/' + options['protocol'] + '/' + options['port'])
                endpoints.append(order(['it:PRIORITY', 'it:IT-TRANSPORT-PROTOCOL-CONFIGURATION', 'it:NETWORK-ENDPOINT-REF', 'it:DISCOVERY-TECHNOLOGY', 'it:SERIALIZATION-TECHNOLOGY', 'it:REMOTING-TECHNOLOGY'], {
                    '@ID': appl_endpoint_id,
                    'it:PRIORITY': { 'fx:PRIORITY': 1 },
                    'it:IT-TRANSPORT-PROTOCOL-CONFIGURATION': {
                        'it:UDP-TP': {
                            'it:UDP-PORT': { 'it:PORT-NUMBER': options['port'] }
                        }
                    },
                    'it:NETWORK-ENDPOINT-REF': { '@ID-REF': self._refToId(endpoint_ref) },
                    'it:DISCOVERY-TECHNOLOGY': order(['it:DISCOVERY-TECHNOLOGY-NAME', 'it:VERSION'], {
                        'it:DISCOVERY-TECHNOLOGY-NAME': 'SOME/IP',
                        'it:VERSION': 1
                    }),
                    'it:SERIALIZATION-TECHNOLOGY': order(['it:SERIALIZATION-TECHNOLOGY-NAME', 'it:VERSION'], {
                        'it:SERIALIZATION-TECHNOLOGY-NAME': 'SOME/IP',
                        'it:VERSION': 1
                    }),
                    'it:REMOTING-TECHNOLOGY': order(['it:REMOTING-TECHNOLOGY-NAME', 'it:VERSION'], {
                        'it:REMOTING-TECHNOLOGY-NAME': 'SOME/IP',
                        'it:VERSION': 1
                    }),
                }))

                provided = self._getProvidedServiceInstances(options['svc_instances']['PROVIDED'], appl_endpoint_id)
                if len(provided):
                    endpoints[-1]['it:PROVIDED-SERVICE-INSTANCES'] = {
                        'it:PROVIDED-SERVICE-INSTANCE': provided
                    }

                required = self._getRequiredServiceInstances(options['svc_instances']['REQUIRED'], appl_endpoint_id)
                if len(required):
                    endpoints[-1]['it:CONSUMED-SERVICE-INSTANCES'] = {
                        'it:CONSUMED-SERVICE-INSTANCE': required
                    }

        return endpoints


    def _getProvidedServiceInstances(self, svc_instances, appl_endpoint_id):
        provided_instances = []

        for svc_ns, svc_instance in svc_instances:

            svc_id = self._refToId(svc_instance['SERVICE-INTERFACE-REF']['#text'])

            sif = None
            for si_ns, interface in self.data['someIpDeployments']['values']:
                if_id = self._getId(si_ns, interface)
                if svc_id == if_id:
                    sif = interface['SERVICE-INTERFACE-REF']['#text']
                    break

            if sif is None:
                raise Exception("ARXML-Error: No service interface found for ref %s" % (svc_instance['SERVICE-INTERFACE-REF']['#text']))


            required_ssif_ref = None
            for rssi_ns, rssi in self.data['requiredSomeIpInstances']['values']:
                if svc_instance['SERVICE-INTERFACE-REF']['#text'] == rssi['SERVICE-INTERFACE-REF']['#text']:
                    required_ssif_ref = self._getPath(rssi_ns, rssi)

            if required_ssif_ref is None:
                logging.warning("ARXML-Warning: No required service interface found for ref %s, setting to NOT_FOUND" % (svc_instance['SERVICE-INTERFACE-REF']['#text']))
                required_ssif_ref = '_NOT_FOUND'
                continue
                # raise Exception("ARXML-Error: No provided service interface found for ref %s" % (svc_instance['SERVICE-INTERFACE-REF']['#text']))


            sd = svc_instance['SD-SERVER-CONFIG']

            provided_instances.append(order(['it:INSTANCE-IDENTIFIER', 'service:SERVICE-INTERFACE-REF', 'it:EVENT-HANDLERS', 'it:SD-SERVER-PARAMETER'], {
                '@ID': self._getId(svc_ns, svc_instance),
                'it:INSTANCE-IDENTIFIER': svc_instance['SERVICE-INSTANCE-ID'],
                'service:SERVICE-INTERFACE-REF': {'@ID-REF': self._refToId(sif)},
                'it:EVENT-HANDLERS': {
                    'it:EVENT-HANDLER': self.getProvidedEventHandler(svc_ns, svc_instance, appl_endpoint_id)
                },
                'it:SD-SERVER-PARAMETER': order(['it:TTL', 'it:INITIAL-ANNOUNCE-BEHAVIOR', 'it:ANNOUNCE-CYCLIC-DELAY', 'it:QUERY-RESPONSE-DELAY'], {
                    'it:TTL': sd['SERVICE-OFFER-TIME-TO-LIVE'],
                    'it:INITIAL-ANNOUNCE-BEHAVIOR': order(['it:INITIAL-DELAY', 'it:INITIAL-REPETITIONS-MAX', 'it:INITIAL-REPETITIONS-BASE-DELAY'], {
                        'it:INITIAL-DELAY': order(['fx:MIN-VALUE', 'fx:MAX-VALUE'], {
                            'fx:MIN-VALUE': "PT%sS" % sd['INITIAL-OFFER-BEHAVIOR']['INITIAL-DELAY-MIN-VALUE'],
                            'fx:MAX-VALUE': "PT%sS" % sd['INITIAL-OFFER-BEHAVIOR']['INITIAL-DELAY-MAX-VALUE']
                        }),
                        'it:INITIAL-REPETITIONS-MAX': sd['INITIAL-OFFER-BEHAVIOR']['INITIAL-REPETITIONS-MAX'],
                        'it:INITIAL-REPETITIONS-BASE-DELAY': "PT%sS" % sd['INITIAL-OFFER-BEHAVIOR']['INITIAL-REPETITIONS-BASE-DELAY']
                    }),
                    'it:ANNOUNCE-CYCLIC-DELAY': "PT%sS" % sd['OFFER-CYCLIC-DELAY'],
                    'it:QUERY-RESPONSE-DELAY': order(['fx:MIN-VALUE', 'fx:MAX-VALUE'], {
                        'fx:MIN-VALUE': "PT%sS" % sd['REQUEST-RESPONSE-DELAY']['MIN-VALUE'],
                        'fx:MAX-VALUE': "PT%sS" % sd['REQUEST-RESPONSE-DELAY']['MAX-VALUE']
                    })
                })
            }))

        return provided_instances

    def getProvidedEventHandler(self, _svc_ns, svc_instance, appl_endpoint_id):
        eventHandler = []

        evtGroups = svc_instance['PROVIDED-EVENT-GROUPS']['SOMEIP-PROVIDED-EVENT-GROUP']
        if isinstance(evtGroups, dict):
            evtGroups = [evtGroups]

        for evtGroup in evtGroups:
            event_group_ref_id = self._getEventGroupId(evtGroup)
            self.data['providedEventHandlerIds'][self._refToId(evtGroup['EVENT-GROUP-REF']['#text'])] = event_group_ref_id

            eventHandler.append(order(['it:CONSUMED-EVENT-GROUP-REFS', 'it:APPLICATION-ENDPOINT-REF'], {  # , 'it:SD-SERVER-PARAMETER'
                'it:CONSUMED-EVENT-GROUP-REFS': {
                    'it:CONSUMED-EVENT-GROUP-REF': { '@ID-REF': event_group_ref_id }
                },
                'it:APPLICATION-ENDPOINT-REF': { '@ID-REF': appl_endpoint_id },
#                 'it:SD-SERVER-PARAMETER': order(['it:TTL', 'it:QUERY-RESPONSE-DELAY'], {
#                     'it:TTL': 3,
#                     'it:QUERY-RESPONSE-DELAY': order(['fx:MIN-VALUE', 'fx:MAX-VALUE'], {
#                         'fx:MIN-VALUE': 'PT0.01S',
#                         'fx:MAX-VALUE': 'PT0.01S'
#                     })
#                 })
            }))

        return eventHandler


    def _getRequiredServiceInstances(self, svc_instances, appl_endpoint_id):
        required_instances = []

        for svc_ns, svc_instance in svc_instances:

            provided_ssif_ref = None
            for pssi_ns, pssi in self.data['providedSomeIpInstances']['values']:
                if svc_instance['SERVICE-INTERFACE-REF']['#text'] == pssi['SERVICE-INTERFACE-REF']['#text']:
                    provided_ssif_ref = self._getPath(pssi_ns, pssi)

            if provided_ssif_ref is None:
                logging.warning("ARXML-Warning: No provided service interface found for ref %s, setting to NOT_FOUND" % (svc_instance['SERVICE-INTERFACE-REF']['#text']))
                provided_ssif_ref = '_NOT_FOUND'
                continue
                # raise Exception("ARXML-Error: No provided service interface found for ref %s" % (svc_instance['SERVICE-INTERFACE-REF']['#text']))

            sd = svc_instance['SD-CLIENT-CONFIG']
            if 'SERVICE-FIND-TIME-TO-LIVE' not in sd.keys():
                logging.warning("ARXML-Warning: Required service interface deployment does not contain TTL value: %s", svc_instance['SHORT-NAME'])
                sd['SERVICE-FIND-TIME-TO-LIVE'] = 0

            counter, consumed_if_id = self._getConsumedInterfaceId(self._getId(svc_ns, svc_instance))
            required_instances.append(order(['it:PROVIDED-SERVICE-INSTANCE-REF', 'it:CONSUMED-EVENT-GROUPS', 'it:SD-CLIENT-PARAMETER'], {
                '@ID': consumed_if_id,
                'it:PROVIDED-SERVICE-INSTANCE-REF': {'@ID-REF': self._refToId(provided_ssif_ref)},
                'it:CONSUMED-EVENT-GROUPS': {
                    'it:CONSUMED-EVENT-GROUP': self.getRequiredEventHandler(svc_ns, svc_instance, appl_endpoint_id, counter)
                },
                'it:SD-CLIENT-PARAMETER': order(['it:TTL', 'it:INITIAL-QUERY-BEHAVIOR'], {
                    'it:TTL': sd['SERVICE-FIND-TIME-TO-LIVE'],
                    'it:INITIAL-QUERY-BEHAVIOR': order(['it:INITIAL-DELAY', 'it:INITIAL-REPETITIONS-MAX', 'it:INITIAL-REPETITIONS-BASE-DELAY'], {
                        'it:INITIAL-DELAY': order(['fx:MIN-VALUE', 'fx:MAX-VALUE'], {
                            'fx:MIN-VALUE': "PT%sS" % sd['INITIAL-FIND-BEHAVIOR']['INITIAL-DELAY-MIN-VALUE'],
                            'fx:MAX-VALUE': "PT%sS" % sd['INITIAL-FIND-BEHAVIOR']['INITIAL-DELAY-MAX-VALUE']
                        }),
                        'it:INITIAL-REPETITIONS-MAX': sd['INITIAL-FIND-BEHAVIOR']['INITIAL-REPETITIONS-MAX'],
                        'it:INITIAL-REPETITIONS-BASE-DELAY': "PT%sS" % sd['INITIAL-FIND-BEHAVIOR']['INITIAL-REPETITIONS-BASE-DELAY']
                    }),
                })
            }))

        return required_instances

    def getRequiredEventHandler(self, svc_ns, svc_instance, appl_endpoint_id, consumed_if_counter):
        eventHandler = []

        evtGroups = svc_instance['REQUIRED-EVENT-GROUPS']['SOMEIP-REQUIRED-EVENT-GROUP']
        if isinstance(evtGroups, dict):
            evtGroups = [evtGroups]

        for evtGroup in evtGroups:
            eventHandler.append(order(['service:EVENT-GROUP-REF', 'it:APPLICATION-ENDPOINT-REF'], {
                '@ID': self._getEventGroupId(evtGroup),  # _%i" % consumed_if_counter,
                'service:EVENT-GROUP-REF': { '@ID-REF': self._refToId(evtGroup['EVENT-GROUP-REF']['#text']) },
                'it:APPLICATION-ENDPOINT-REF': { '@ID-REF': appl_endpoint_id }
            }))

        return eventHandler

    def _getEventGroupId(self, evtGroup):
        if not 'providedEventHandlerIds' in self.data.keys():
            self.data['providedEventHandlerIds'] = {}

        key_id = self._refToId(evtGroup['EVENT-GROUP-REF']['#text'])
        if not key_id in self.data['providedEventHandlerIds'].keys():
            self.data['providedEventHandlerIds'][key_id] = self._refToId(evtGroup['EVENT-GROUP-REF']['#text']) + "_event_group"

        return self.data['providedEventHandlerIds'][key_id]


    def _getConsumedInterfaceId(self, if_id):
        if not 'consumedInterfaceIds' in self.data.keys():
            self.data['consumedInterfaceIds'] = {}

        key_id = self._refToId(if_id)
        if not key_id in self.data['consumedInterfaceIds'].keys():
            self.data['consumedInterfaceIds'][key_id] = 0
        self.data['consumedInterfaceIds'][key_id] += 1
        return self.data['consumedInterfaceIds'][key_id], if_id  # + '_%i' % self.data['consumedInterfaceIds'][key_id]

