from abc import *


class ILandTaxCal(metaclass=ABCMeta):
    @abstractmethod
    def calAcquisitionTax(self, acquisitionPrice, py, numofHouse):
        pass
    @abstractmethod
    def calLongteramHoldingDeductionRate(self, realLive, liveYears, holdingYears):
        pass
    @abstractmethod
    def getLiveYears(self):
        pass
    @abstractmethod
    def setLiveYears(self, year):
        pass


class landTaxCal_1216(ILandTaxCal):
    def __init__(self):
        pass
    def calAcquisitionTax(self, acquisitionPrice, py, numofHouse):
        pass
    def calLongteramHoldingDeductionRate(self, realLive, liveYears, holdingYears):
        pass
    def getLiveYears(self):
        pass
    def setLiveYears(self, year):
        pass

class landTaxCal_0706(ILandTaxCal):
    def __init__(self):
        pass
    def calAcquisitionTax(self, acquisitionPrice, py, numofHouse):
        pass
    def calLongteramHoldingDeductionRate(self, realLive, liveYears, holdingYears):
        pass
    def getLiveYears(self):
        pass
    def setLiveYears(self, year):
        pass

class LandTaxCal:
    def __init__(self, landInfo):
        self.land = list()

        # if(self.SelctTaxBase(landInfo["acqutionDate"][4])):
        pass
    def SelectTaxCalInterface(self, acqutionDate, transferDate):
        pass
    def SelectTaxBase(self, acqDate):
        pass
    def CalTax(self):
        pass



