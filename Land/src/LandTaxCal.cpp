#include <LandTaxCal.h>

using namespace std;

void LandTaxCal::addInfo(int numhouse)
{
    setNumofHouse(numhouse_);

    cout << " please input your house name ";
    cin >> title_;

    cout << " input jointTenancy  true(1) or fasle(0) : ";
    cin >> jointTenancy_;

    cout << " input squrea meter(py) : ";
    cin >> py_;

    cout << " input actual duration of stay(years) : ";
    cin >> liveYears_;

    cout << " input acquisition Date : ";
    cin >> acquisitionDate_;

    cout << " input Transfer Date : ";
    cin >> transferDate_;

    cout << " input acquisition Price : ";
    cin >> acquisitionPrice_;

    cout << " input transfer Price : ";
    cin >> transferPrice_;
}

void LandTaxCal::setHouseTilte(const std::string& titleHouse) { title_ = titleHouse; }
void LandTaxCal::setNumofHouse(const int& numofHouse)   { numhouse_ = numofHouse; }
void LandTaxCal::setPy(const int& py)   { py_ = py; }
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
    cout << endl << "Your House Number is : [" << numhouse_ + 1  << "]" << setw(2) << std::endl;
    cout << "jointTenancy" << setw(2) << " : " << setw(2) << right << jointTenancy_ << std::endl;
    cout << "acquisitionPrice" << setw(2) << " : " << setw(2) << right << acquisitionPrice_ << std::endl;
    cout << "acquisitionDate" << setw(2) << " : " << setw(2) << right << acquisitionDate_ << std::endl;
    cout << "transferPrice" << setw(2) << " : " << setw(2) << right << transferPrice_ << std::endl;
    cout << "transferDate" << setw(2) << " : " << setw(2) << right << transferDate_ << std::endl;
    cout << "tranferMargin" << setw(2) << " : " << setw(2) << right << tranferMargin_ << std::endl;
    cout << "commmision" << setw(2) << " : " << setw(2) << right << commmision_ << std::endl;
    cout << "years : " << setw(2) << right << years_ << std::endl;
    cout << "liveYears : " << setw(2) << right << liveYears_ << std::endl;
    cout << "py : " << setw(2) << right << py_ << std::endl;
    cout << "tax : " << setw(2) << right << tax_ << std::endl;

    fflush(stdin);
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
    if (numhouse_ == 1)  longTermDeductuibRate *= calLongteramHoldingDeductionRate(getReallive2year(), getActualDurationofStay(), getHoldingYears());
    else                    longTermDeductuibRate *= 0;

    taxBaseTransferMargin -= (taxBaseTransferMargin * longTermDeductuibRate);

    // 인별 양도소득금액
    if (getJointTenacy() > 1) {
        taxBaseTransferMargin /= getJointTenacy();
    }

    // 과세표준
    taxBaseTransferMargin -= basicDeduction;

    // 양도소득세율
    double trasferMarginTaxRate = getTrasferMarginTaxRate(taxBaseTransferMargin);

    // 누진공제액
    double progressiveTax = getProgressiveTax(trasferMarginTaxRate);

    // 감면세액
    double deductionTax = 0; // TBD

    // 양도소득세 = 과세표준 * 양도소득세율 - 누진공제액 - 감면세액
    double retTax = taxBaseTransferMargin * trasferMarginTaxRate - deductionTax - progressiveTax;

    //지방소득세(10%)
    retTax *= 1.1;

    // 인별 납부금액
    if (getJointTenacy() > 1) {
        retTax *= getJointTenacy();
    }

    return retTax;
}

void LandTaxCal::expectLandRevnue(double diffence)
{
    vector<std::pair<double, double>> expectedRevenue;

    for(int i=0; i < 5; i++) {
        double transferPrice = getTransferPrice() + (i * diffence);
        double expectedTax = calExpectedTax(transferPrice);
        expectedRevenue.push_back({transferPrice, expectedTax});
    }

    cout << "양도가액" << setw(20) << "세금" << setw(20) << "손익" << endl;
    for(auto revenue : expectedRevenue) {
        cout << revenue.first << setw(20) << revenue.second << setw(20) << revenue.first - revenue.second << endl;
    }
    cout << endl << "please input any button" << endl;
    fflush(stdin);
    getchar(); getchar();

    // TBD(save Json file)
}

void LandTaxCal::expectLandRevnuebyYear(int endYear)
{
    vector<std::pair<double, double>> expectedRevenue;
    // TBD
}

void LandTaxCal::saveRevenue()
{
    cout << "================== " << __func__  << "===================================" << endl;


}

void LandTaxCal::drawRevenue()
{
    cout << "================== " << __func__ << "===================================" << endl;
}

