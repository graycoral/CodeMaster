import json


class ConfigJson:
    def __init__(self, path):
        with open(path, 'r') as f:
            self.jsonData = json.load(f)
            self.testData = self.jsonData['TC_COM']
            self.unicast = self.jsonData['unicast']
            self.multicast = self.jsonData['multicast']
            self.cts_ipaddress = self.jsonData['cts_config']['ip']
            self.cts_port = self.jsonData['cts_config']['port']

    def GetTestCase(self):
        return self.testData

    def ReadTestCaseDesc(self, idx):
        k, v = self.testData[idx].items()
        print("[{}] : {}".format(k, v[0]["desc"]))

    def ReadAllDesc(self):
        idx = 1
        for k, v in sorted(self.testData.items()):
            print("[{}] [{}] : {}".format(idx, k, v[0]["desc"]))
            idx += 1
