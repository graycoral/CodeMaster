#include "../inc/LandTaxCal.h"

using namespace std;

void LandTaxCal::addInfo()
{
    cout << " input your number of House : ";
    cin >> numhouse_;
    setNumofHouse(numhouse_);

    cout << " input jointTenancy  true(1) or fasle(0) : ";
    cin >> jointTenancy_;
    setJointTenacy(jointTenancy_);

    cout << " input squrea meter(py) : ";
    cin >> py_;
    setJointTenacy(jointTenancy_);

    cout << " input actual duration of stay(years) : ";
    cin >> liveYears_;
    setActualDurationofStay(liveYears_);

    cout << " input acquisition Date : ";
    cin >> acquisitionDate_;
    setAcquisitionDate(acquisitionDate_);

    cout << " input Transfer Date : ";
    cin >> transferDate_;
    setTransferDate(transferDate_);

    cout << " input acquisition Price : ";
    cin >> acquisitionPrice_;
    setAcquisitionPrice(acquisitionPrice_);

    cout << " input transfer Price : ";
    cin >> transferPrice_;
    setTransferPrice(transferPrice_);
}

void LandTaxCal::setNumofHouse(const int& numofHouse)   { numhouse_ = numofHouse; }
void LandTaxCal::setJointTenacy(const bool& jointTenancy)
{
    if (jointTenancy == 1 || jointTenancy == 0) {
        jointTenancy_ = jointTenancy;
    }
    else {
        cout << " Invalid Input " << endl;
        jointTenancy_ = false;
    }
}
void LandTaxCal::setAcquisitionPrice(const double& acquisitionPrice) {acquisitionPrice_ = acquisitionPrice; }
void LandTaxCal::setTransferPrice(const double& transferPrice)
{
    transferPrice_ = transferPrice;
    calTransferMargin(transferPrice_,  py_, acquisitionPrice_);
}

int LandTaxCal::calYearfromDate(string acquisitionDate, string transferDate)
{
    int retYears = 0;
    int month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    try {
        int acqYear = std::stoi(acquisitionDate.substr(0, 4));
        int trasYear = std::stoi(transferDate.substr(0, 4));
        int acqMonth = std::stoi(acquisitionDate.substr(4, 2));
        int trasMonth = std::stoi(transferDate.substr(4, 2));
        int acqDay = std::stoi(acquisitionDate.substr(6, 2));
        int trasDay = std::stoi(transferDate.substr(6, 2));
        int acquisitionDays = (acqYear * 365) + month[acqMonth] + acqDay;
        int transferDays = (trasYear * 365) + month[trasMonth] + trasDay;

        retYears = (transferDays - acquisitionDays) / 365;
    }
    catch (const std::out_of_range & e) {
        cout << "out of range " << endl;
    }

    return retYears;
}

void LandTaxCal::setAcquisitionDate(const string&  acquisitionDate)
{
    acquisitionDate_= acquisitionDate;
}

void LandTaxCal::setTransferDate(const string&  transferDate)
{
    transferDate_= transferDate;
    years_ = calYearfromDate(acquisitionDate_, transferDate_);
    if(landTax == 0)    {
        if(transferDate_ > TransferDate_1216)           landTax = new landTaxCal_1216(years_);
        else if (transferDate_ > TransferDate_0706)     landTax = new landTaxCal_0706(liveYears_, years_);
        else {
            cout << "Invalid Transfer Date" << endl;
        }
    }
}

void LandTaxCal::calTransferMargin(double transferPrice, int py, double acquisitionPrice)
{
    extraExpense_ += commmision_ + landTax->calAcquisitionTax(acquisitionPrice, py, numhouse_);
    tranferMargin_ = transferPrice- acquisitionPrice - extraExpense_;
}

double LandTaxCal::getTransferMargin()
{
    return tranferMargin_;
}

void LandTaxCal::show()
{
    cout << "================== " << __func__  << "===================================" << endl;
    cout << "numhouse_" << setw(2) << " : " << setw(2) << right << numhouse_ << std::endl;
    cout << "jointTenancy_" << setw(2) << " : " << setw(2) << right << jointTenancy_ << std::endl;
    cout << "acquisitionPrice_" << setw(2) << " : " << setw(2) << right << acquisitionPrice_ << std::endl;
    cout << "acquisitionDate_" << setw(2) << " : " << setw(2) << right << acquisitionDate_ << std::endl;
    cout << "transferPrice_" << setw(2) << " : " << setw(2) << right << transferPrice_ << std::endl;
    cout << "transferDate_" << setw(2) << " : " << setw(2) << right << transferDate_ << std::endl;
    cout << "tranferMargin_" << setw(2) << " : " << setw(2) << right << tranferMargin_ << std::endl;
    cout << "commmision_" << setw(2) << " : " << setw(2) << right << commmision_ << std::endl;
    cout << "years_ : " << setw(2) << right << years_ << std::endl;
    cout << "liveYears_ : " << setw(2) << right << liveYears_ << std::endl;
    cout << "py_ : " << setw(2) << right << py_ << std::endl;
    cout << "tax_ : " << setw(2) << right << tax_ << std::endl;

    int test;

    cout << endl << "please input any button";
    fflush(stdin);  getchar();
    getchar();
}

void LandTaxCal::setTaxBaseTransferMargin(const double& taxBaseTransferMargin)
{
    taxBaseTransferMargin_ = taxBaseTransferMargin;
}

double LandTaxCal::calLongteramHoldingDeductionRate(bool realLive, int years, int holingYears)
{
    return landTax->calLongteramHoldingDeductionRate(realLive, years, holingYears) / 100;
}

int LandTaxCal::getAssementStandardTaxBase()
{
    int retAssementStandardTaxBase = 1;

    return retAssementStandardTaxBase;
}

double LandTaxCal::getTrasferMarginTaxRate(double taxBaseTransferMargin)
{
    if (taxBaseTransferMargin <= 12e6)          return 0.06;
    else if(taxBaseTransferMargin <= 46e6)      return 0.15;
    else if(taxBaseTransferMargin <= 88e6)      return 0.24;
    else if (taxBaseTransferMargin <= 15e7)     return 0.35;
    else if (taxBaseTransferMargin <= 3e8)      return 0.38;
    else if (taxBaseTransferMargin <= 5e8)      return 0.4;
    else                                        return 0.42;
}

double LandTaxCal::getProgressiveTax(double trasferMarginTaxRate)
{
    if (trasferMarginTaxRate <= 0.06)       return 0;
    else if (trasferMarginTaxRate <= 0.15)  return 108e4;
    else if (trasferMarginTaxRate <= 0.24)  return 522e4;
    else if (trasferMarginTaxRate <= 0.35)  return 149e5;
    else if (trasferMarginTaxRate <= 0.38)  return 194e5;
    else if (trasferMarginTaxRate <= 0.4)   return 254e5;
    else                                    return 354e5;
}


double LandTaxCal::calExpectedTax(double transferPrice)
{
    // 양도차액
    double transferMargin = transferPrice - getAcquisitionPrice() - extraExpense_;
    double basicDeduction = calYearfromDate(getAcquisitionDate(), getTransferDate_()) * 25e6; // 연 1회 인별 250만원 공제 적용 과세표준

    // 과세대상 양도 차액
    double taxBaseTransferMargin = transferPrice >= 1e9 ? transferMargin * (transferPrice - 1e9) / transferPrice : 0;

    // 장기보유 특별 공제
    int longTermDeductuibRate = 1;
    if (numhouse_ == 1)  longTermDeductuibRate *= calLongteramHoldingDeductionRate(landTaxCal->getReallive2year(), landTaxCal->getActualDurationofStay(), landTaxCal->getHoldingYears());
    else                    longTermDeductuibRate *= 0;

    taxBaseTransferMargin -= (taxBaseTransferMargin * longTermDeductuibRate);
}

void LandTaxCal::expectLandRevnue(LandTaxCal landTaxCal ,double diffence)
{
    vector<std::pair<double, double>> expectedRevenue;

    for(int i=0; i < 5; i++) {
        double transferPrice = getTransferPrice() + (i * diffence);
        double expectedTax = calExpectedTax(transferPrice);
        expectedRevenue.push_back({transferPrice, expectedTax});
    }
    // TBD(save Json file)
}

void LandTaxCal::saveRevenue()
{
    cout << "================== " << __func__  << "===================================" << endl;


}

void LandTaxCal::drawRevenue()
{
    cout << "================== " << __func__ << "===================================" << endl;
}

