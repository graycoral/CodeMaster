
import logging
import xmltodict

from XMLDataConverter import XMLDataConverter
from util.Exception import CliError
from util.Singleton import Singleton


class ARXMLParser(Singleton):
    """
    A ARXML file parser class
    """

    @classmethod
    def init(cls):
        # not needed from system manifest: MODE-DECLARATION-GROUP,

        cls.elements = {
            'serviceInterfaces':         {'id': "SERVICE-INTERFACE", 'values': []},
            'executables':               {'id': "EXECUTABLE", 'values': []},
            'processes':                 {'id': "PROCESS", 'values': []},
            'adaptiveApplications':      {'id': "ADAPTIVE-AUTOSAR-APPLICATION", 'values': []},
            'startupConfigSets':         {'id': "STARTUP-CONFIG-SET", 'values': []},
            'aaSwComponentTypes':        {'id': "ADAPTIVE-APPLICATION-SW-COMPONENT-TYPE", 'values': []},
            'swBaseTypes':               {'id': "SW-BASE-TYPE", 'values': []},
            'implementationDatatypes':   {'id': "IMPLEMENTATION-DATA-TYPE", 'values': []},
            'compuMethods':              {'id': "COMPU-METHOD", 'values': []},
            'appPrimitiveDatatypes':     {'id': "APPLICATION-PRIMITIVE-DATA-TYPE", 'values': []},
            'datatypeMappingSets':       {'id': "DATA-TYPE-MAPPING-SET", 'values': []},
            'ethernetCluster':           {'id': "ETHERNET-CLUSTER", 'values': []},
            'machines':                  {'id': "MACHINE", 'values': []},
            'someIpDeployments':         {'id': "SOMEIP-SERVICE-INTERFACE-DEPLOYMENT", 'values': []},
            'someIpTransformerProps':    {'id': "SOMEIP-DATA-PROTOTYPE-TRANSFORMATION-PROPS", 'values': []},
            'requiredSomeIpInstances':   {'id': "REQUIRED-SOMEIP-SERVICE-INSTANCE", 'values': []},
            'providedSomeIpInstances':   {'id': "PROVIDED-SOMEIP-SERVICE-INSTANCE", 'values': []},
            'svcInstToPortProtMappings': {'id': "SERVICE-INSTANCE-TO-PORT-PROTOTYPE-MAPPING", 'values': []},
            'svnInstToMachineMappings':  {'id': 'SOMEIP-SERVICE-INSTANCE-TO-MACHINE-MAPPING', 'values': []}
        }


    @classmethod
    def extractData(cls, configurations):

        for configuration in configurations:
            content = ARXMLParser.parseFile(configuration.arxmlFile)

            for key, el in cls.elements.items():
                cls.elements[key]['values'].extend(ARXMLParser.findElementsWithNamespace(content, el['id']))

        return XMLDataConverter(cls.elements)

    @classmethod
    def stats(cls):
        logging.info("Found:")

        for key, el in cls.elements.items():
            logging.info("# %i %s", len(el['values']), key)


    @classmethod
    def parseFile(cls, fileName):
        """
        It is intended to find the frames in the trace file.
        It calls helper method self._parseAsciiFile which does the main parsing part

        @return: list of frames
        """

        plain_xml = open(fileName).read()

        try:
            parsed_xml = xmltodict.parse(plain_xml)
        except Exception as ex:
            raise CliError("Failed parsing ARXML file %s: %s" % (fileName, ex))

        if 'AUTOSAR' in parsed_xml.keys():
            parsed_xml = parsed_xml['AUTOSAR']
        else:
            raise CliError("Not an AUTOSAR ARXML file: %s" % fileName)

        return parsed_xml

    @classmethod
    def findElementsWithNamespace(cls, xml, tag, ns=[], found=[], runFirst=True):
        if runFirst:
            found = []

        # do the recursive traversal, until tag is found

        if not isinstance(xml, dict):  # empty container
            return

        for key in xml.keys():
            item = xml[key]

            if isinstance(item, list):  # found many items, process them one by one
                for k in item:
                    cls._processItem(k, key, tag, ns, found, False)
            else:
                cls._processItem(item, key, tag, ns, found, False)

        return found

    @classmethod
    def _processItem(cls, item, key, tag, ns, found, runFirst):
        if key == tag:
            found.append((ns, item))

        elif key in ["AR-PACKAGES", "ELEMENTS"]:
            cls.findElementsWithNamespace(item, tag, ns, found, False)
        elif key == "AR-PACKAGE":
            # add shortname to namespace
            new_copy = ns[:]
            new_copy.append(item["SHORT-NAME"])
            cls.findElementsWithNamespace(item, tag, new_copy, found, False)













