import unittest
from src import testcase


class SkeletonTest(unittest.TestCase):
    # TODO: 순서 설정??
    def test_001(self):
        payload_list = ['', '0100']
        ret = testcase.TC_CM_005(payload_list, 0x1234)
        self.assertTrue(ret)

    def test_002(self):
        ret = testcase.TC_CM_002()
        self.assertTrue(ret)