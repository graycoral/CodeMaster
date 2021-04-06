#!/usr/local/bin/python3.5
# encoding: utf-8

from argparse import ArgumentParser
from argparse import RawDescriptionHelpFormatter
import argparse
import glob
import logging
import os
import sys

from ARXMLParser import ARXMLParser
from FIBEXCreator import FIBEXCreator
from util.ArxmlFileConfiguration import ArxmlFileConfiguration


DEBUG = 1
PROFILE = 0

logger = logging.getLogger("")  # default logger, before other logger are set up pylint: disable=invalid-name


class callCounter(object):
    '''
    Decorator to determine number of calls for a method
    '''

    def __init__(self, method):
        self.method = method
        self.count = 0

    def __call__(self, *args, **kwargs):
        self.count += 1
        return self.method(*args, **kwargs)

logger.warning = callCounter(logger.warning)  # append count decorator
logger.error = callCounter(logger.error)  # append count decorator


def _enableLogging(configuration=None, consoleLevel=logging.INFO, filename=None):
    """
    Enables logging for a configuration. The filename derives from the configurations trace file.
    @param configuration: a TraceFileConfiguration object
    @param consoleLevel: the logging level for console output
    @param filename: when no configuration is passed, a filename could be provided for the logfile
    """

    # if configuration is set, filename is being overridden !
    if configuration:
        filename = configuration.getOutputFolder() + configuration.getArxmlName() + "_log.txt"

    fmt = "[%(asctime)s][%(levelname)s][%(filename)s:%(lineno)d]" + " %(message)s"
    datefmt = "%H:%M:%S"

    # get logger to attach file and console handlers
    myLogger = logging.getLogger("")
    myLogger.handlers = []
    myLogger.setLevel(logging.DEBUG)

    # set formatter for log messages
    formatter = logging.Formatter(fmt)
    formatter.datefmt = datefmt

    # create console handler
    console = logging.StreamHandler()
    console.setLevel(consoleLevel)
    console.setFormatter(formatter)

    if filename is not None:
        # create file handler
        fh = logging.FileHandler(filename)
        fh.setLevel(logging.INFO)
        fh.setFormatter(formatter)

    # attach console and file handlers to logger
    myLogger.addHandler(console)
    if filename is not None:
        myLogger.addHandler(fh)

    logging.info("Log filename: %s", filename)

def _addArgumentDefinitions(parser):
    """
    Adds Arguments to argument parser object; that is needed to parse command line arguments
    @param parser: the argument parser object
    """
    assert isinstance(parser, ArgumentParser)


    parser.add_argument(
        "-v",
        "--verbose",
        dest="verbose",
        action="count",
        help="set verbosity level [default: %(default)s]"
    )

    parser.add_argument(
        dest="paths",
        help="paths to folder(s) with source file(s) [default: %(default)s]",
        metavar="path",
        nargs='+'
    )

    parser.add_argument(
        r"-d",
        r"--output",
        type=str,
        metavar=r"OutputFolder",
        help=r"The folder where the generated output should be saved"
    )

    parser.add_argument(
        r"-p",
        r"--project-name",
        type=str,
        metavar=r"ProjectName",
        default="SOMEIP",
        help=r"The project name to be created"
    )

    parser.add_argument(
        r"-f",
        r"--fibex",
        type=str,
        metavar=r"OutputFilename",
        default="FBX4.xml",
        help=r"The name of the FIBEX file that is created"
    )

def _validateInputArguments(args):
    """
    Check passed arguments and transform them into expected data types
    @param args: the arguments object created by argparser
    """
    assert isinstance(args, argparse.Namespace)



def _createConfigurationObjects(args):
    """
    Create ArxmlFileConfiguration objects.
    @param args: the arguments object created by argparser
    """
    assert isinstance(args, argparse.Namespace)

    configurations = []

    files = []
    for path in args.paths:
        # get arxml files of this path
        files.extend(glob.glob(os.path.join(path, "*.arxml")))


    for arxmlFile in files:
        # create new TraceFileConfiguration instance
        absTraceFile = os.path.abspath(arxmlFile)
        config = ArxmlFileConfiguration(absTraceFile)

        # set properties from arguments
        config.outputFolder = args.output
        configurations.append(config)

    return configurations



def main(argv=None):  # IGNORE:C0111
    """
    Main function of Arxml2CANoe:
     - argument parsing
     - creating instances of configurations)
     - start conversion
    """
    programName = os.path.basename(sys.argv[0])
    programDesc = '''Copyright 2018 Vector Informatik GmbH. All rights reserved.\n\nUSAGE'''

    try:
        # Setup argument parser
        parser = ArgumentParser(description=programDesc, formatter_class=RawDescriptionHelpFormatter)

        _addArgumentDefinitions(parser)  # add argument definitions to parser
        args = parser.parse_args()  # get input arguments
        _validateInputArguments(args)  # validate input arguments

        configurations = _createConfigurationObjects(args)

        _enableLogging(consoleLevel=logging.DEBUG if args.verbose else logging.INFO)
        # for configuration in configurations:
            # _enableLogging(configuration, logging.DEBUG if args.verbose else logging.INFO)


        ARXMLParser.init()
        data = ARXMLParser.extractData(configurations)
        ARXMLParser.stats()

        data.setArgs(args)

        FIBEXCreator.init()
        FIBEXCreator.fillData(data)
        FIBEXCreator.save(args)
        FIBEXCreator.stats()

        logging.info("Done.")

        if logging.getLogger("").error.count:
            return 1
        elif logging.getLogger("").warning.count:
            return 2
        else:
            return 0  # ok

    except KeyboardInterrupt:
        ### handle keyboard interrupt ###
        return 3
    except Exception as e:  # pylint: disable=broad-except
        if DEBUG:
            raise e
        indent = len(programName) * " "
        sys.stderr.write(programName + ": " + repr(e) + "\n")
        sys.stderr.write(indent + "  for help use --help")
        return 1  # error


if __name__ == "__main__":
    if PROFILE:
        import cProfile  # pylint: disable=wrong-import-position, wrong-import-order
        import pstats  # pylint: disable=wrong-import-position, wrong-import-order
        profile_filename = 'main_profile.txt'  # pylint: disable=invalid-name
        cProfile.run('main()', profile_filename)
        statsfile = open("profile_stats.txt", "wb")  # pylint: disable=invalid-name
        p = pstats.Stats(profile_filename, stream=statsfile)  # pylint: disable=invalid-name
        stats = p.strip_dirs().sort_stats('cumulative')  # pylint: disable=invalid-name
        stats.print_stats()
        statsfile.close()
        sys.exit(0)
    sys.exit(main())
