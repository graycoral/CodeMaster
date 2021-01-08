import sys
import argparse
import time
import threading
import logging

from unittest import TestLoader, TestSuite
from HtmlTestRunner import HTMLTestRunner

from testcase.testSuites import TC_CM
from testcase.testcase import *
from cts_manager import *


### Simple commandline parser ###
def parseCommandLine():
    parser = argparse.ArgumentParser(description='AUTOSAR COM Test Suite(CTS)')
    parser.add_argument('-c', metavar='Configuration Path [optional]', default="config.json",
                        help='config.json is default')
    parser.add_argument('-o', metavar='output file [optional]',
                        default=time.strftime('%Y-%m-%d', time.localtime(time.time())) + "CTS_Test_Result.html",
                        help='Add the path to the output file. Default path: localtime_CTS_Test_Result.html')
    parser.add_argument('-m', metavar='Test Mode(single, all) [optional]', type=str, default="single",
                        help='Test Mode(single, all)')

    return parser.parse_args()


def make_logger(name=None):
    logger = logging.getLogger(name)
    logger.setLevel(logging.DEBUG)

    formatter = logging.Formatter("[%(asctime)s][%(name)s][%(levelname)s] %(message)s")
    console = logging.StreamHandler()

    file_handler = logging.FileHandler(filename="CTS.log")
    console.setLevel(logging.INFO)
    file_handler.setLevel(logging.DEBUG)

    console.setFormatter(formatter)
    file_handler.setFormatter(formatter)

    logger.addHandler(console)
    logger.addHandler(file_handler)

    return logger

def run(tc, all_test_cases=False):
    if all_test_cases is True:
        for i in range(0, len(tc.GetTestCase())):
            tc.read_test_case_desc(i)
            tc.run_test_case(i)
    else:
        while True:
            try:
                tc.read_test_case_all_desc()
                print("\n Enter test number:", end=' ')
                idx = int(input())
                tc.run_test_case(idx - 1)
            except ValueError:
                print("Invalid Test Index")
                continue
            except:
                sys.exit()

def main():
    logger = make_logger('CTS')

    args = parseCommandLine()
    testMode = args.m
    if testMode == 'single':
        testcase = TestCase(logger)
        run(testcase)
        saveResult()
    else:
        testCM = TestLoader().loadTestsFromTestCase(TC_CM)
        suite = TestSuite([testCM])
        runner = HTMLTestRunner(output='../TestResult', report_name='LARA_COM_Test_Result',
                                report_title='LARA COM Test Result', combine_reports=True)
        runner.run(suite)


if sys.version_info < (3, 8):
    sys.exit('This program requires Python version 3.8 or newer!')

if __name__ == '__main__':
    main()
