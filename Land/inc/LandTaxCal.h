#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const string TransferDate_1216("1216");
const string TransferDate_0706("0706");

class ILandTaxCal
{
    virtual double calTax() = 0;

};

class landTaxCal_1216 : public ILandTaxCal
{
    virtual double calTax() override
    {
        cout << "landTaxCal_1216" << endl;
    }
};

class landTaxCal_0706 : public ILandTaxCal
{
    virtual double calTax() override
    {
        cout << "landTaxCal_0706" << endl;
    }
};

class LandTaxCal
{
    ILandTaxCal* landTax;

public:
    LandTaxCal() { }
private:
    int numhouse_;                  // 주택수
    bool jointTenancy_;             // 공동명의
    double acquisitionPrice_;       // 취득가액
    string acquisitionDate_;        // 취득일자
    double transferPrice_;          // 양도가액
    string transferDate_;           // 양도일자
    double tranferMargin_;          // 양도차액
    double extraExpense_;           // 기타경비
    double tax_;                    // 양도소득세
    double commmision_;             // 복비

public:
    void setNumofHouse(const int& numofHouse);
    void setJointTenacy(const bool& jointTenancy);
    void setAcquisitionPrice(const double& acquisitionPrice);
    void setTransferPrice(const double& transferPrice);
    void setAcquisitionDate(const string&  acquisitionDate);
    void setTransferDate(const string&  transferDate);
    void show();
    void input();
    void updateData();
    double calTransferMargin(double transferPrice, double acquisitionPrice);

    // TBD
    void drawRevenue()    {            }
    void saveRevenue()    {            }
};