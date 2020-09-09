import re
import openpyxl
from openpyxl.chart import LineChart, Reference, BarChart

charList = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'

class Excel:
    def __init__(self):
        self.wb = openpyxl.Workbook()
        self.pos = 0
        self.posPrice = charList[self.pos]
        self.posData = charList[self.pos + 1]
        self.posGrid = charList[self.pos] + '10'

    def gridChart(self, sh, idx):
        chart = LineChart()
        cData = Reference(sh, min_col=self.pos + 2, min_row=1, max_row=sh.max_row)
        chart.add_data(cData, titles_from_data=True)
        cat1 = Reference(sh, min_row= 2, max_row=sh.max_row, min_col=self.pos + 1)
        chart.set_categories(cat1)
        sh.add_chart(chart, self.posGrid)

    def saveData(self, data, name, idx):
        sh = self.wb.active
        sh[self.posPrice + '1'] = name +" 매도가격"
        sh[self.posData + '1'] = name + " 수익"

        cnt = 2
        for d in data:
            sh[self.posPrice + str(cnt)] = d[0]
            sh[self.posData + str(cnt)] = d[1]
            cnt += 1

        self.gridChart(sh, idx)
        self.write()
        self.pos += 2
        self.posPrice = charList[self.pos]
        self.posData = charList[self.pos + 1]
        self.posGrid = charList[self.pos + 5] + '10'

    def write(self):
        self.wb.save('LandCal.xlsx')



