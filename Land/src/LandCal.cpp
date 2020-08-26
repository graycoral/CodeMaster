#include <LandCal.h>

using namespace std;

void LandCal::init()
{
    if( getNumofHoouses() == 0) {
        cout << "No Land Info : " << kJsonPath << endl;
        addLandInfo(increaseNumofHouse(), false);
    } else {
        for(int i= 0; i < numoofHouse_ ; i++) {
            addLandInfo(i, true);
        }
    }
}

int LandCal::readData()
{
    LandConfiguration readJson(kJsonPath, numoofHouse_, name_);
    return numoofHouse_;
}

void LandCal::showMain()
{
    cout << "[1] Add your house Info" << endl;
    cout << "[2] Save Data to Excel" << endl;
    cout << "[3] Update your house Info" << endl;
    cout << "[4] show your house Info and Tax" << endl;
    cout << "[5] Expect Your Reveue and Tax" << endl;
    cout << "[6] Exit" << endl << endl;

    cout << "please select number : ";
}

void LandCal::addLandInfo(int idx, bool database)
{
    cout << "Add Land your info" << endl;
    std::shared_ptr<LandTaxCal> landTax = makeLandInfo(idx, database);
    calTax(landTax);
    landTaxCal.push_back(landTax);
    
    if(database == false)
        readJson.AddNewLandInfo(idx, landTax);
}

void LandCal::updateLandInfo()
{
    int houseIdx;
    cout << "please Info house Id what you want to update" << endl;
    cin >> houseIdx;
}

int LandCal::getAssementStandardTaxBase(LandTaxCal landTaxCal, double standardTaxBase)
{
    return landTaxCal.getAssementStandardTaxBase();
}

void LandCal::calTax(std::shared_ptr<LandTaxCal> landTaxCal)
{
    string csTax= "tax";
    double tax = landTaxCal->calExpectedTax(landTaxCal->getTransferPrice());
    landTaxCal->setTax(tax);
    //readJson.AddNewHouseInfo(landTaxCal->getHouseTitle().c_str(), "tax", tax);
    readJson.AddNewHouseInfo("test", "tax", tax);
}

void LandCal::showLandInfo()
{
    cout << "number of house : " << numoofHouse_ << endl;
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

std::shared_ptr<LandTaxCal> LandCal::makeLandInfo(int num, bool database = false)
{
    std::shared_ptr<LandTaxCal> retLandInfo = std::make_shared<LandTaxCal>();

    if(database == true) readJson.AddLandInfo(num, retLandInfo);
    else retLandInfo->addInfo(num+1);

    return retLandInfo;
}

void LandCal::saveDatatoExcel()
{
    cout << "================== " << __func__ << "===================================" << endl;
}