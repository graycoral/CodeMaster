import unittest
import threading
from src.testcase.testcase import *
from src.cts_manager.cts_manager import CtsManager


def cts_process(send_tc_num):
    lock_ = threading.Lock()
    logger_ = logging.getLogger('TEST_SUITE')
    logger_.setLevel(logging.DEBUG)
    cts_manager_ = CtsManager(lock_, logger_)
    cts_manager_.process_initial_cts_manager('127.0.0.1', 2500)
    cts_manager_.send_test_case(send_tc_num)
    lock_.acquire()

class TC_CM(unittest.TestCase):
    def test_001(self):
        cts_process('TC_CM_001')
        ret = TC_CM_001()
        self.assertTrue(ret)

    def test_002(self):
        cts_process('TC_CM_002')
        ret = TC_CM_002()
        self.assertTrue(ret)

    def test_003(self):
        cts_process('TC_CM_003')
        ret = TC_CM_003()
        self.assertTrue(ret)

    def test_004(self):
        cts_process('TC_CM_004')
        ret = TC_CM_004()
        self.assertTrue(ret)

    def test_005(self):
        cts_process('TC_CM_005')
        ret = TC_CM_005()
        self.assertTrue(ret)

    def test_007(self):
        cts_process('TC_CM_007')
        ret = TC_CM_007()
        self.assertTrue(ret)

    def test_008(self):
        cts_process('TC_CM_008')
        ret = TC_CM_008()
        self.assertTrue(ret)

    def test_009(self):
        cts_process('TC_CM_009')
        ret = TC_CM_009()
        self.assertTrue(ret)

    def test_012(self):
        cts_process('TC_CM_012')
        ret = TC_CM_012()
        self.assertTrue(ret)
