import json

class Landjson:
    def __init__(self):
        self.expectedRevenue = []
        self.jsonData = {}
        self.numHouse = 0

    def readJson(self):
        with open('./etc/landinfo.json', 'r') as f:
            self.jsonData = json.load(f)
            self.numHouse = int(self.jsonData['houses']['numofhouse'])
        # print(json.dumps(self.jsonData, indent="\t"))

    def getNumofHouse(self):
        return self.numHouse

    def saveExpectedRevenue(self):
        for i in range(0, self.numHouse):
            # print(self.jsonData['houses']['houseInfos'][i]['expectedRevenue'])
            revenue = []
            cnt = 0
            for d in self.jsonData['houses']['houseInfos'][i]['expectedRevenue']:
                diffValue = self.jsonData['houses']['houseInfos'][i]['diff']
                transferPrice = self.jsonData['houses']['houseInfos'][i]['transferPrice'] + (diffValue*cnt)
                revenue.append((transferPrice, self.jsonData['houses']['houseInfos'][i]['expectedRevenue'][cnt]))
                cnt += 1

            self.expectedRevenue.append(revenue)