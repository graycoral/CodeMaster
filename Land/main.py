import os
import sys

import LandExcel
import LandJson

def main():
    print("execute python LandCalculator")

    readJsonData = LandJson.Landjson()
    ExcelData = LandExcel.Excel()

    for i in range(readJsonData.getNumofHouses()):
        ExcelData.saveData(readJsonData.saveExpectedRevenue(i), readJsonData.geTileofHouse(i), i)

if __name__ == '__main__':
    main()

