'''
Created on Mar 27, 2018

@author: viseng
'''

import logging
import os
import xmltodict

from util import order
from util.Singleton import Singleton


class FIBEXCreator(Singleton):
    """
    A FIBEX file creator class
    """
    @classmethod
    def init(cls):
        pass


    @classmethod
    def fillData(cls, data):

        fx_data = {
            'fx:FIBEX': order(['@xmlns:xsi', '@xmlns:fx', '@xmlns:ho', '@xmlns:ethernet', '@xmlns:it', '@xmlns:service', '@xsi:schemaLocation', '@VERSION', 'fx:PROJECT', 'fx:ELEMENTS', 'fx:PROCESSING-INFORMATION'], {
                '@xmlns:xsi': 'http://www.w3.org/2001/XMLSchema-instance',
                '@xmlns:fx': 'http://www.asam.net/xml/fbx',
                '@xmlns:ho': 'http://www.asam.net/xml',
                '@xmlns:ethernet': 'http://www.asam.net/xml/fbx/ethernet',
                '@xmlns:it': 'http://www.asam.net/xml/fbx/it',
                '@xmlns:service': 'http://www.asam.net/xml/fbx/services',

                '@xsi:schemaLocation': r"http://www.asam.net/xml/fbx .\xml_schema\fibex.xsd       http://www.asam.net/xml/fbx/ethernet .\xml_schema\fibex4ethernet.xsd       http://www.asam.net/xml/fbx/it .\xml_schema\fibex4it.xsd       http://www.asam.net/xml/fbx/services .\xml_schema\fibex4services.xsd",

                '@VERSION': '4.1.1',

                'fx:PROJECT': data.getProject(),
                'fx:ELEMENTS': order(['fx:CLUSTERS', 'fx:CHANNELS', 'fx:ECUS', 'fx:SERVICE-INTERFACES', 'fx:DATATYPES'], {
                    'fx:CLUSTERS': data.getNetworkClusters(),
                    'fx:CHANNELS': data.getChannels(),
                    'fx:ECUS': data.getEcus(),
                    'fx:SERVICE-INTERFACES': data.getServiceInterfaces(),
                    'fx:DATATYPES': data.getDatatypes(),
                }),
                'fx:PROCESSING-INFORMATION': {
                    'fx:CODINGS': data.getCodings()
                }
            })
        }

        # recursive replace namespace by URL
        # cls._replaceNsByUrl(fx_data)

        cls.fx_xml = xmltodict.unparse(
            fx_data,
#             namespaces=cls.namespaces,
            pretty=True,
        )


#     @classmethod
#     def _replaceNsByUrl(cls, data):
#         for key, item in data.items():
#             for ns, url in cls.reverse_namespace.items():
#                 if ns + ":" in key:
#                     data[key.replace(ns + ":", url + ":")] = data.pop(key)
#                     break
#
#             if isinstance(item, dict):
#                 cls._replaceNsByUrl(item)

    @classmethod
    def save(cls, args):
        filename = os.path.join(args.output, args.fibex)
        fd = open(filename, 'w')
        fd.write(cls.fx_xml)
        fd.close()
        logging.info("Saved file: %s", filename)

    @classmethod
    def stats(cls):
        # logging.info("Created document:")

        logging.debug("FIBEX content:\n%s", cls.fx_xml)
        pass

