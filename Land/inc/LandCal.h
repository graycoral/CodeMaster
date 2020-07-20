#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>

#include "LandTaxCal.h"

#define clrscr()    system("clear")

using namespace std;

class LandCal
{
    vector<std::shared_ptr<LandTaxCal>> landTaxCal;
public:
    LandCal() : numoofHouse_(0) {}
    void showMain();
    void addLandInfo();
    void calTax(std::shared_ptr<LandTaxCal> landTaxCal);
    void saveDatatoExcel();
    void updateLandInfo();
    void showLandInfo(const LandCal& land);
    void expectLandRevnue(const LandCal& landCal, double diffence);
    int getAssementStandardTaxBase(LandTaxCal landTaxCal, double standardTaxBase);
    std::shared_ptr<LandTaxCal> makeLandInfo();
private:
    int numoofHouse_;
};