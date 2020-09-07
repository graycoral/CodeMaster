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
    std::shared_ptr<LandTaxCal> landTax = makeLandInfo(idx, database);
    calTax(landTax);
    landTaxCal.push_back(landTax);

    if(database == false)
        readJson.AddNewLandInfo(idx, landTax);
}

void LandCal::updateLandInfo()
{
    int houseIdx;
    string member;
    int idx = 0;

    for(auto v : landTaxCal) {
        cout << ++idx << " : "<< v->getHouseTitle() << endl;
    }
    cout << "please Info house Id what you want to update" << endl;
    cin >> houseIdx;

    cout << "please Input what you want memeber" << endl;
    cin >> member;

    if((member == "name") || (member == "acqutionDate") || (member == "transferDate")) {
        string newValue;
        cout << "please Input new name" << endl;        cin >> newValue;
        readJson.ModifyStringLandInfo(landTaxCal[houseIdx-1]->getHouseTitle(), member, newValue);
        if(member == "name")    landTaxCal[houseIdx-1]->setHouseTilte(newValue);
        else if(member == "acqutionDate")    landTaxCal[houseIdx-1]->setAcquisitionDate(newValue);
        else if(member == "transferDate")    landTaxCal[houseIdx-1]->setTransferDate(newValue);
    } else if(member == "jointTenancy") {
        bool newValue;
        cout << "please Input new name" << endl;        cin >> newValue;
        readJson.ModifyLandInfo(landTaxCal[houseIdx-1]->getHouseTitle(), member, newValue);
        landTaxCal[houseIdx-1]->setJointTenacy(newValue);
    }
    else if((member == "squreMeter") || (member == "liveYears")) {
        int newValue;
        cout << "please Input new value" << endl;        cin >> newValue;
        readJson.ModifyLandInfo(landTaxCal[houseIdx-1]->getHouseTitle(), member, newValue);
        if(member == "squreMeter")    landTaxCal[houseIdx-1]->setPy(newValue);
        else if(member == "liveYears")    landTaxCal[houseIdx-1]->setActualDurationofStay(newValue);
    }
    else if((member == "acqutionPrice") || (member == "transferPrice")) {
        double newValue;
        cout << "please Input new name" << endl;
        cin >> newValue;
        readJson.ModifyLandInfo(landTaxCal[houseIdx-1]->getHouseTitle(), member, newValue);
    } else {
        cout << "please check out what you want to update value" << endl;
    }
}

int LandCal::getAssementStandardTaxBase(LandTaxCal landTaxCal, double standardTaxBase)
{
    return landTaxCal.getAssementStandardTaxBase();
}

void LandCal::calTax(std::shared_ptr<LandTaxCal> landTaxCal)
{
    double tax = landTaxCal->calExpectedTax(landTaxCal->getTransferPrice());
    landTaxCal->setTax(tax);
    readJson.AddNewHouseInfo(landTaxCal->getHouseTitle().c_str(), "tax", tax);
}

void LandCal::showLandInfo()
{
    cout << "number of house : " << numoofHouse_ << endl;
    for (auto v : landTaxCal) {
        v->show();
    }
    cout << endl << "please input any button" << endl;
}

void LandCal::expectLandRevnue(const LandCal& landCal)
{
    if(getNumofHoouses()) {
        double diffValue = 0; string housenum;

        cout << "please input what you want differce of value : ";
        cin >> diffValue;
        cout << "please input your house number or All: (eg, 1 or A(all)" ;
        cin >> housenum;
        if (housenum == "Y" || "y") {
            for( int i =0; i < getNumofHoouses(); i++ ){
                landTaxCal[i]->expectLandRevnue(diffValue);
                readJson.AddNewHouseInfo(landTaxCal[i]->getHouseTitle(), "diff", diffValue);
                readJson.AddExpectLandRevnue(i, landTaxCal[i]->getExpectedRevenue());
            }
        } else {
            int hNum = std::stoi(housenum) -1;
            landTaxCal[hNum-1]->expectLandRevnue(diffValue);
            readJson.AddExpectLandRevnue(hNum-1, landTaxCal[hNum-1]->getExpectedRevenue());
        }
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
    readJson.SaveData();
    // system("python3 main.py")

}