#include <iostream>
#include <string>

using namespace std;


const string TransferDate_1216 = "1216";
const string TransferDate_0706 = "0706";

class ILandTaxCal
{
    virtual double calTax() = 0;

};

class landTaxCal_1216 : public ILandTaxCal
{
    virtual double calTax() override
    {

    }
};

class landTaxCal_0706 : public ILandTaxCal
{
    virtual double calTax() override
    {

    }
};

class LandTaxCal
{
    ILandTaxCal* landTax;
    string transferDate_;           // 양도일자
public:
    LandTaxCal() { }
    LandTaxCal(ILandTaxCal* cal, string transferDate) : landTax(cal), transferDate_(transferDate)
    {
        if(cal == 0)    landTax = new landTaxCal_1216;
        else {
            if(transferDate_ > TransferDate_1216)           landTax = new landTaxCal_1216;
            else if (transferDate_ > TransferDate_0706)     landTax = new landTaxCal_0706;
            else {
                cout << "Invalid Transfer Date" << endl;
            }

        }
    }
private:
    int numhouse_;                  // 주택수
    bool jointTenancy_;             // 공동명의
    double acquisitionPrice_;       // 취득가액
    double transferPrice_;          // 양도가액
    string acquisitionDate_;        // 취득일자
    //string transferDate_;           // 양도일자

public:
    void setNumofHouse(const int& numofHouse)   { numhouse_ = numofHouse; }
    void setJointTenacy(const bool& jointTenancy)  { jointTenancy_ = jointTenancy; }
    void setAcquisitionPrice(const double& acquisitionPrice) {acquisitionPrice_ = acquisitionPrice; }
    void setTransferPrice(const double& transferPrice)
    {
        transferPrice_ = transferPrice;
        if(landTax == 0)    {
            if(transferDate_ > TransferDate_1216)           landTax = new landTaxCal_1216;
            else if (transferDate_ > TransferDate_0706)     landTax = new landTaxCal_0706;
            else {
                cout << "Invalid Transfer Date" << endl;
            }
        }
    }
    void setAcquisitionDate(const string&  acquisitionDate) { acquisitionDate_= acquisitionDate; }
    void setTransferDate(const string&  transferDate) { transferDate_= transferDate; }

    void show();


    // TBD
    void drawRevenue()    {            }
    void saveRevenue()    {            }
};