#include <LandCal.h>
#include "landConfigurartion/LandConfigurartion.h"

using namespace std;

// static constexpr const char kJsonPath[] = "./etc/landinfo.json";
const std::string kJsonPath = "../etc/landinfo.json";

void LandCal::init()
{
    cout << "================== " << __func__  << "===================================" << endl;
    if( readData() == 0) {
        cout << "No Land Info : " << kJsonPath << endl;
        addLandInfo();
    }
}

int LandCal::readData()
{
    int numofHouse = 0;
    // LandConfiguration readJson;
    cout << "================== " << __func__  << "===================================" << endl;
    LandConfiguration readJson(kJsonPath);

    return numofHouse;
}

void LandCal::showMain()
{
    // clrscr();
    cout << "[1] Add your house Info" << endl;
    cout << "[2] Save Data to Excel" << endl;
    cout << "[3] Update your house Info" << endl;
    cout << "[4] show your house Info and Tax" << endl;
    cout << "[5] Expect Your Reveue and Tax" << endl;
    cout << "[6] Exit" << endl << endl;

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
    double tax = landTaxCal->calExpectedTax(landTaxCal->getTransferPrice());
    landTaxCal->setTax(tax);
}

void LandCal::showLandInfo(const LandCal& landCal)
{
    cout << "================== " << __func__ << "===================================" << endl;
    cout << "number of house : " << landCal.numoofHouse_ << endl;
    cout << "number of house : " << this->numoofHouse_ << endl;
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