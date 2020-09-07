import json

class Landjson:
    def __init__(self):
        self.expectedRevenue = []
        self.jsonData = {}
        self.numHouse = 0

    def readJson(self):
        with open('./etc/landinfo.json', 'r') as f:
            self.jsonData = json.load(f)
        # print(json.dumps(self.jsonData, indent="\t"))

    def saveExpectedRevenue(self):
        # expectedRevenue = []
        self.numHouse = int(self.jsonData['houses']['numofhouse'])
        for i in range(0, self.numHouse):
            self.expectedRevenue.append(self.jsonData['houses']['houseInfos'][i]['expectedRevenue'])