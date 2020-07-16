#include "../inc/Land.h"
#include "../inc/LandTaxCal.h"

using namespace std;

void Land::showMain()
{
    cout << "================== " << __func__  << "===================================";
    cout << "1. Add your house Info" << endl;
    cout << "2. Calculate Tax" << endl;
    cout << "3. Save Data to Excel" << endl;
    cout << "4. Update your house Info" << endl << endl;
    cout << "please select number : ";
    //cout << "양도소득세 : " << setw(10) << right << tax_ << std::endl;
    cout << "================== " << __func__  << "===================================";
}

void Land::addLandInfo()
{
    cout << "Add Land your info" << endl;
    numoofHouse_++;
    std::shared_ptr<LandTaxCal> land = makeLandInfo();
    landCal.push_back(land);
}

void Land::calTax()
{
    cout << "================== " << __func__  << "===================================";
}

void Land::saveDatatoExcel()
{
    cout << "================== " << __func__  << "===================================";
}

void Land::updateLandInfo()
{
    cout << "================== " << __func__  << "===================================";
}

std::shared_ptr<LandTaxCal> Land::makeLandInfo()
{
    cout << "================== " << __func__  << "===================================";
}