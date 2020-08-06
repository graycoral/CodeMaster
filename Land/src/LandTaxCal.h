#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>

using namespace std;

const string TransferDate_1216("1216");
const string TransferDate_0706("0706");

class ILandTaxCal
{
public:
    ILandTaxCal(int liveYears) : liveYears_(liveYears), holdngYears_(liveYears) {}
    ILandTaxCal(int liveYears, int holdngYears) : liveYears_(liveYears), holdngYears_(holdngYears) {}
    virtual double calAcquisitionTax(double acquisitionPrice, int py, int numofHouse) = 0;
    virtual int calLongteramHoldingDeductionRate(bool realLive, int liveYears, int holdingYears) = 0;
    virtual int getLiveYears() = 0;
    virtual void setLiveYears(int years) = 0;
public:
    int liveYears_;
    int holdngYears_;
};

class landTaxCal_1216 : public ILandTaxCal
{
public:
    landTaxCal_1216(int liveYears) : ILandTaxCal(liveYears) {}
    virtual void setLiveYears(int years) { liveYears_ = years; }
    virtual int getLiveYears() { return liveYears_; }
    virtual int calLongteramHoldingDeductionRate(bool realLive, int liveYears, int holdingYears)
    {
        int retDeductionRate = 0;
        if (realLive) retDeductionRate = holdingYears * 8;
        else		  retDeductionRate = holdingYears * 2;

        return retDeductionRate;
    }

    virtual double calAcquisitionTax(double acquisitionPrice, int py, int numofHouse) override
    {
        double retAcquisitionTax = 0;
        if (numofHouse <= 3) {
            if (acquisitionPrice < 6e9) {
                if(py < 85) retAcquisitionTax = acquisitionPrice * 0.011;
                else retAcquisitionTax = acquisitionPrice * 0.013;
            } else if (acquisitionPrice < 9e9) {
                if (py < 85) retAcquisitionTax = acquisitionPrice * 0.022;
                else retAcquisitionTax = acquisitionPrice * 0.024;
            }
            else {
                if (py < 85) retAcquisitionTax = acquisitionPrice * 0.033;
                else retAcquisitionTax = acquisitionPrice * 0.035;
            }
        }
        else {
            retAcquisitionTax = acquisitionPrice * 0.04;
        }

        return retAcquisitionTax;
    }
};

class landTaxCal_0706 : public ILandTaxCal
{
public:
    landTaxCal_0706(int liveYears, int holdingYears) : ILandTaxCal(liveYears, holdingYears) {}
    virtual void setLiveYears(int years) { liveYears_ = years; }
    virtual int getLiveYears() { return liveYears_; }
    virtual int calLongteramHoldingDeductionRate(bool realLive, int liveYears, int holdingYears)
    {
        int retDeductionRate = 0;
        if (realLive) retDeductionRate = holdingYears * 8;
        else		  retDeductionRate = holdingYears * 2;

        return retDeductionRate;
    }

    virtual double calAcquisitionTax(double acquisitionPrice, int py, int numofHouse) override
    {
        double retAcquisitionTax = 0;
        if (numofHouse <= 1) {
            if (acquisitionPrice < 6e9) {
                if (py < 85) retAcquisitionTax = acquisitionPrice * 0.011;
                else retAcquisitionTax = acquisitionPrice * 0.013;
            }
            else if (acquisitionPrice < 9e9) {
                if (py < 85) retAcquisitionTax = acquisitionPrice * 0.022;
                else retAcquisitionTax = acquisitionPrice * 0.024;
            }
            else {
                if (py < 85) retAcquisitionTax = acquisitionPrice * 0.033;
                else retAcquisitionTax = acquisitionPrice * 0.035;
            }
        }
        else if (numofHouse <= 2) {
            if (py < 85) retAcquisitionTax = acquisitionPrice * 0.083;
            else retAcquisitionTax = acquisitionPrice * 0.085;
        }
        else {
            retAcquisitionTax = acquisitionPrice * 0.125;
        }

        return retAcquisitionTax;
    }
};

class LandTaxCal
{
    ILandTaxCal* landTax;

public:
    LandTaxCal() : numhouse_(0), jointTenancy_(false), acquisitionPrice_(0), transferPrice_(0),
        tranferMargin_(0), extraExpense_(0), tax_(0), commmision_(0), landTax(0), years_(0), acquisitionTax_(0) { }
private:
    string title_;                  // 집 이름
    int numhouse_;                  // 주택수
    bool jointTenancy_;             // 공동명의
    bool reallive2years_;           // 2년거주
    double acquisitionPrice_;       // 취득가액
    double acquisitionTax_;			// 취득세
    string acquisitionDate_;        // 취득일자
    double transferPrice_;          // 양도가액
    string transferDate_;           // 양도일자
    double tranferMargin_;          // 양도차액
    double taxBaseTransferMargin_;	// 과세대상 양도 차액
    double extraExpense_;           // 기타경비
    double tax_;                    // 납부 세액(양도소득세)
    double commmision_;             // 복비
    int years_;                     // 보유기간
    int liveYears_;                 // 실제 거주기간
    int py_;                        // 평수

public:
    void setNumofHouse(const int& numofHouse);
    void setJointTenacy(const bool& jointTenancy);
    bool getJointTenacy() { return jointTenancy_; };
    void setAcquisitionPrice(const double& acquisitionPrice);
    double getAcquisitionPrice() { return acquisitionPrice_; };
    void setTransferPrice(const double& transferPrice);
    double getTransferPrice() { return transferPrice_; };
    void setTaxBaseTransferMargin(const double& taxBaseTransferMargin);
    double getTaxBaseTransferMargin() { return taxBaseTransferMargin_; };
    void setAcquisitionDate(const string&  acquisitionDate);
    void setTransferDate(const string&  transferDate);
    void setActualDurationofStay(int years) { liveYears_ = years; }
    int getActualDurationofStay() { return liveYears_; }
    void show();
    void addInfo(int numhouse);
    void updateData();
    void calTransferMargin(double transferPrice, int py, double acquisitionPrice);
    double getTransferMargin();
    int calYearfromDate(string acquisitionDate, string transferDate);
    bool getReallive2year() { return reallive2years_; }
    int getAssementStandardTaxBase();
    int getHoldingYears() { return years_; }
    double calLongteramHoldingDeductionRate(bool realLive, int years, int holingYears);
    void setTax(double tax) { tax_ = tax; }
    double getTrasferMarginTaxRate(double taxBaseTransferMargin);
    double getProgressiveTax(double trasferMarginTaxRate);
    string getAcquisitionDate()     {  return acquisitionDate_; }
    string getTransferDate_()       {  return transferDate_; }

    double calExpectedTax(double transferPrice);
    void expectLandRevnue(double diffence);
    void expectLandRevnuebyYear(int enbdYear);

    // TBD
    void drawRevenue();
    void saveRevenue();
};