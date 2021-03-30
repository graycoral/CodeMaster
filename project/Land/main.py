import os
import sys

import LandExcel
import LandJson
import LandQT

from PyQt5.QtWidgets import *

def main():
    print("execute python LandCalculator")

    readJsonData = LandJson.Landjson()
    readJsonData.readJson()
    readJsonData.saveExpectedRevenue()

    ExcelData = LandExcel.Excel()
    ExcelData.saveData(readJsonData.expectedRevenue)
    ExcelData.gridChart()
    ExcelData.write()

    print("execute LandQT")
    app = QApplication(sys.argv)
    landQT = LandQT.LandQt()

    app.exec()

if __name__ == '__main__':
    main()