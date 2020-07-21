#include "../inc/LandCal.h"

using namespace std;

void LandCal::showMain()
{
    // clrscr();
    cout << "1. Add your house Info" << endl;
    cout << "2. Save Data to Excel" << endl;
    cout << "3. Update your house Info" << endl;
    cout << "4. show your house Info and Tax" << endl;
    cout << "5. Expect Your Reveue and Tax" << endl;
    cout << "6. Exit" << endl << endl;

    cout << "please select number : ";
}

void LandCal::addLandInfo()
{
    cout << "Add Land your info" << endl;
    numoofHouse_++;
    std::shared_ptr<LandTaxCal> landTax = makeLandInfo();
    calTax(landTax);
    landTaxCal.push_back(landTax);
}

int LandCal::getAssementStandardTaxBase(LandTaxCal landTaxCal, double standardTaxBase)
{
    return landTaxCal.getAssementStandardTaxBase();
}

void LandCal::calTax(std::shared_ptr<LandTaxCal> landTaxCal)
{
    cout << "================== " << __func__  << "===================================" << endl;
#if 0
    // 양도차액
    double transferMargin = landTaxCal->getTransferMargin();
    double basicDeduction = landTaxCal->calYearfromDate( landTaxCal->getAcquisitionDate(), landTaxCal->getTransferDate_()) * 25e6; // 연 1회 인별 250만원 공제 적용 과세표준

    // 과세대상 양도 차액
    double taxBaseTransferMargin = landTaxCal->getTransferPrice() >= 1e9 ? transferMargin * (landTaxCal->getTransferPrice() - 1e9) / landTaxCal->getTransferPrice() : 0;
    landTaxCal->setTaxBaseTransferMargin(taxBaseTransferMargin);

    // 장기보유 특별 공제
    int longTermDeductuibRate = 1;
    if (numoofHouse_ == 1)  longTermDeductuibRate *= landTaxCal->calLongteramHoldingDeductionRate(landTaxCal->getReallive2year(), landTaxCal->getActualDurationofStay(), landTaxCal->getHoldingYears());
    else                    longTermDeductuibRate *= 0;

    taxBaseTransferMargin -= (taxBaseTransferMargin * longTermDeductuibRate);

    // 인별 양도소득금액
    if (landTaxCal->getJointTenacy() > 1) {
        taxBaseTransferMargin /= landTaxCal->getJointTenacy();
    }

    // 과세표준
    taxBaseTransferMargin -= basicDeduction;

    // 양도소득세율
    double trasferMarginTaxRate = landTaxCal->getTrasferMarginTaxRate(taxBaseTransferMargin);

    // 누진공제액
    double progressiveTax = landTaxCal->getProgressiveTax(trasferMarginTaxRate);

    // 감면세액
    double deductionTax = 0; // TBD

    // 양도소득세 = 과세표준 * 양도소득세율 - 누진공제액 - 감면세액
    double tax = taxBaseTransferMargin * trasferMarginTaxRate - deductionTax - progressiveTax;

    //지방소득세(10%)
    tax *= 1.1;

    // 인별 납부금액
    if (landTaxCal->getJointTenacy() > 1) {
        tax *= landTaxCal->getJointTenacy();
    }

#endif
    double tax = landTaxCal->calExpectedTax(landTaxCal->getTransferPrice());
    landTaxCal->setTax(tax);
}

void LandCal::showLandInfo(const LandCal& landCal)
{
    cout << "================== " << __func__ << "===================================" << endl;
    cout << "number of house : " << landCal.numoofHouse_ << endl;
    for (auto v : landTaxCal) {
        v->show();
    }
    cout << endl << "please input any button";
}

void LandCal::expectLandRevnue(const LandCal& landCal)
{
    cout << "================== " << __func__ << "===================================" << endl;

    if(getNumofHoouses()) {
        double diffValue = 0; int housenum = 0;
        cout << "please input what you want differce of value : ";
        cin >> diffValue;
        cout << "please input your house number : " ;
        cin >> housenum;
        landCal.landTaxCal[housenum-1]->expectLandRevnue(diffValue);
    }
    else {
        cout << "please input your house info before expecting land revenue" << endl;
    }

}

std::shared_ptr<LandTaxCal> LandCal::makeLandInfo()
{
    cout << "================== " << __func__ << "===================================" << endl;
    std::shared_ptr<LandTaxCal> retLandInfo= std::make_shared<LandTaxCal>();
    retLandInfo->addInfo();

    return retLandInfo;
}

void LandCal::saveDatatoExcel()
{
    cout << "================== " << __func__ << "===================================" << endl;
}

void LandCal::updateLandInfo()
{
    cout << "================== " << __func__ << "===================================" << endl;
}