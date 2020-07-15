#include "../inc/LandTaxCal.h"

using namespace std;

void LandTaxCal::input()
{
    cout << " input your number of House : ";
    cin >> numhouse_;
    setNumofHouse(numhouse_);

    cout << " input jointTenancy  true(1) or fasle(0) : ";
    cin >> jointTenancy_;
    setJointTenacy(jointTenancy_);

    cout << " input acquisition Price : ";
    cin >> acquisitionPrice_;
    setAcquisitionPrice(acquisitionPrice_);

    cout << " input transfer Price : ";
    cin >> transferPrice_;
    setTransferPrice(transferPrice_);

    cout << " input acquisition Date : ";
    cin >> acquisitionDate_;
    setAcquisitionDate(acquisitionDate_);

    cout << " input Transfer Date : ";
    cin >> transferDate_;
    setTransferDate(transferDate_);
}

void LandTaxCal::setNumofHouse(const int& numofHouse)   { numhouse_ = numofHouse; }
void LandTaxCal::setJointTenacy(const bool& jointTenancy)  { jointTenancy_ = jointTenancy; }
void LandTaxCal::setAcquisitionPrice(const double& acquisitionPrice) {acquisitionPrice_ = acquisitionPrice; }
void LandTaxCal::setTransferPrice(const double& transferPrice)
{
    transferPrice_ = transferPrice;
    calTransferMargin(transferPrice_,  acquisitionPrice_);
}

void LandTaxCal::setAcquisitionDate(const string&  acquisitionDate) { acquisitionDate_= acquisitionDate; }
void LandTaxCal::setTransferDate(const string&  transferDate)
{
    transferDate_= transferDate;
    if(landTax == 0)    {
        if(transferDate_ > TransferDate_1216)           landTax = new landTaxCal_1216;
        else if (transferDate_ > TransferDate_0706)     landTax = new landTaxCal_0706;
        else {
            cout << "Invalid Transfer Date" << endl;
        }
    }
}

double LandTaxCal::calTransferMargin(double transferPrice, double acquisitionPrice)
{
    tranferMargin_ = transferPrice_- acquisitionPrice_;
    return tranferMargin_;
}

void LandTaxCal::show()
{
    cout << "================== " << __func__  << "===================================";
    cout << "주택수 : " << setw(10) << right << numhouse_ << std::endl;
    cout << "공동명의 : " << setw(10) << right << jointTenancy_ << std::endl;
    cout << "취득가액 : " << setw(10) << right << acquisitionPrice_ << std::endl;
    cout << "취득일자 : " << setw(10) << right << acquisitionDate_ << std::endl;
    cout << "양도가액 : " << setw(10) << right << transferPrice_ << std::endl;
    cout << "양도일자 : " << setw(10) << right << transferDate_ << std::endl;
    cout << "양도차액 : " << setw(10) << right << tranferMargin_ << std::endl;
    cout << "복비 : " << setw(10) << right << commmision_ << std::endl;
    cout << "양도소득세 : " << setw(10) << right << tax_ << std::endl;
    cout << "================== " << __func__  << "===================================";
}

void LandTaxCal::saveRevenue()
{
    cout << "================== " << __func__  << "===================================";
    cout << "================== " << __func__  << "===================================";

}

