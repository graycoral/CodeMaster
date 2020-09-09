import json

class Landjson:
    def __init__(self):
        self.expectedRevenue = []
        self.jsonData = {}
        with open('./etc/landinfo.json', 'r') as f:
            self.jsonData = json.load(f)
        self.numHouse = int(self.jsonData['houses']['numofhouse'])


    def getNumofHouses(self):
        return int(self.jsonData['houses']['numofhouse'])

    def geTileofHouse(self, idx):
        return self.jsonData['houses']['houseInfos'][idx]['name']

    def saveExpectedRevenue(self, idx):
        revenue = []
        cnt = 0

        for d in self.jsonData['houses']['houseInfos'][idx]['expectedRevenue']:
            diffValue = self.jsonData['houses']['houseInfos'][idx]['diff']
            transferPrice = self.jsonData['houses']['houseInfos'][idx]['transferPrice'] + (diffValue * cnt)
            revenue.append((str(round(transferPrice/100000000, 2)) + '억', self.jsonData['houses']['houseInfos'][idx]['expectedRevenue'][cnt]))
            cnt += 1
        # self.expectedRevenue.append(revenue)
        print("revenue : ", revenue )
        return revenue
