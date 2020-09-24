import sys

from PyQt5.QtWidgets import *
from PyQt5.uic import loadUi
from PyQt5.QtCore import *

import LandJson

class AddLand:
    def __init__(self):
        self.dlg = loadUi('AddLand.ui')
        self.dlg.pushButton.clicked.connect(self.fn)
        self.dlg.exec()  # 모달다이아로그

    def fn(self):
        self.dlg.close()


class LandQt:
    def __init__(self):
        self.dlg = loadUi('LandCal.ui')
        self.dlg.pushButtonCalLand.clicked.connect( self.calLandTax)
        self.dlg.pushButtonAddLand.clicked.connect( self.addLand)
        self.readData()
        self.dlg.show()

    def readData(self):
        savedData = LandJson.Landjson()
        savedData.readJson()

        for i in range(0, savedData.getNumofHouse()):
            self.insertTableData(savedData.jsonData['houses']['houseInfos'][i], i)

    def insertTableData(self, landInfo, idx):
        nCol = self.dlg.tableWidget.columnCount()
        self.dlg.tableWidget.setColumnCount(nCol + 1)
        self.dlg.tableWidget.setItem(0, nCol, QTableWidgetItem(str(landInfo['name'])))
        self.dlg.tableWidget.setItem(1, nCol, QTableWidgetItem(str(landInfo['jointTenancy'])))
        self.dlg.tableWidget.setItem(2, nCol, QTableWidgetItem(str(idx + 1)))
        self.dlg.tableWidget.setItem(3, nCol, QTableWidgetItem(str(landInfo['liveYears'])))
        self.dlg.tableWidget.setItem(4, nCol, QTableWidgetItem(str(landInfo['acqutionPrice'] / 100000000) + '억'))
        self.dlg.tableWidget.setItem(5, nCol, QTableWidgetItem(str(landInfo['transferPrice'] / 100000000) + '억'))
        self.dlg.tableWidget.setItem(6, nCol, QTableWidgetItem(str(landInfo['acqutionDate'][:4]+'년 ' + \
                                                                   landInfo['acqutionDate'][4:6] +'월 '+ \
                                                                   landInfo['acqutionDate'][6:8] +'일')))
        self.dlg.tableWidget.setItem(7, nCol, QTableWidgetItem(str(landInfo['transferDate'][:4]+'년 ' + \
                                                                   landInfo['transferDate'][4:6] +'월 ' + \
                                                                   landInfo['transferDate'][6:8] +'일')))

    def calLandTax(self):
        pass

    def addLand(self):
        addLand = AddLand()

    def menuClick(self):
        # o = OtherDlg() #hang
        # s = o.dlg.lineEditChild.text()
        # self.dlg.lineEditMain.setText( s )
        print('click...')

    def fn(self):
        pass



