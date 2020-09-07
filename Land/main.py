import os
import sys

import LandExcel
import LandJson

def main():
    print("execute python LandCalculator")

    readJsonData = LandJson.Landjson()
    readJsonData.readJson()
    readJsonData.saveExpectedRevenue()

    ExcelData = LandExcel.Excel()
    ExcelData.saveData(readJsonData.expectedRevenue)
    ExcelData.gridChart()

if __name__ == '__main__':
    main()

