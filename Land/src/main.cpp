#include <iostream>

using namespace std;

#include "../inc/BaseLand.h"

int numhouse_;                  // 주택수
bool jointTenancy_;             // 공동명의
double acquisitionPrice_;       // 취득가액
double transferPrice_;          // 양도가액
string acquisitionDate_;        // 취득일자
string transferDate_;           // 양도일자

void input(LandTaxCal& landcal)
{
    cout << " input your number of House : ";
    cin >> numhouse_;
    landcal.setNumofHouse(numhouse_);
    cout << endl;

    cout << " input jointTenancy  true(1) or fasle(0) : ";
    cin >> jointTenancy_;
    landcal.setJointTenacy(jointTenancy_);
    cout << endl;

    cout << " input acquisition Price : ";
    cin >> acquisitionPrice_;
    landcal.setAcquisitionPrice(acquisitionPrice_);
    cout << endl;

    cout << " input transfer Price : ";
    cin >> transferPrice_;
    landcal.setTransferPrice(transferPrice_);
    cout << endl;

    cout << " input acquisition Date : ";
    cin >> acquisitionDate_;
    landcal.setAcquisitionDate(acquisitionDate_);
    cout << endl;

    cout << " input Transfer Date : ";
    cin >> transferDate_;
    landcal.setTransferDate(transferDate_);
    cout << endl;
}

int main(int argc, const char* argv[])
{
    cout << "========== Hello Land Tax Calculator ==========" << endl;
    LandTaxCal landCal;

    while(1) {
        //landCal.show();
        input(landCal);

    }
}