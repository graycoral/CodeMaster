import unittest
import testcase


class ProxyTest(unittest.TestCase):
    def test_001(self):
        payload_list = ['0100']  # 256(uint16)
        ret = testcase.TC_CM_012(2000, payload_list)
        self.assertTrue(ret)

    def test_002(self):
        payload_list = ['010000008200000156000001be']  # active = 01
        ret = testcase.TC_CM_009(2000, payload_list)
        self.assertTrue(ret)
