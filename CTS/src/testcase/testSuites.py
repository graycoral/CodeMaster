import unittest
from testcase.testcase import *
from cts_manager.cts_manager import CtsManager


class TC_CM(unittest.TestCase, CtsManager):
    def test_001(self):
        ret = TC_CM_001(CtsManager)
        self.assertTrue(ret)

    def test_002(self):
        ret = TC_CM_009(CtsManager)
        self.assertTrue(ret)

    def test_003(self):
        ret = TC_CM_003(CtsManager)
        self.assertTrue(ret)

    def test_004(self):
        ret = TC_CM_004(CtsManager)
        self.assertTrue(ret)

    def test_005(self):
        ret = TC_CM_005(CtsManager)
        self.assertTrue(ret)

    def test_007(self):
        ret = TC_CM_007(CtsManager)
        self.assertTrue(ret)

    def test_008(self):
        ret = TC_CM_008(CtsManager)
        self.assertTrue(ret)

    def test_009(self):
        ret = TC_CM_009(CtsManager)
        self.assertTrue(ret)

    def test_012(self):
        ret = TC_CM_012(CtsManager)
        self.assertTrue(ret)
