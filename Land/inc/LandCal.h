#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>

#include <LandTaxCal.h>
#include <rapidjson/document.h>     // rapidjson's DOM-style API
#include <rapidjson/prettywriter.h> // for stringify JSON

#define clrscr()    system("clear")

using namespace std;

class LandCal
{
    vector<std::shared_ptr<LandTaxCal>> landTaxCal;
public:
    LandCal() : numoofHouse_(0) {}
    void init(const LandCal& landCal);
    void readData();
    void showMain();
    void addLandInfo();
    void calTax(std::shared_ptr<LandTaxCal> landTaxCal);
    void saveDatatoExcel();
    void updateLandInfo();
    void showLandInfo(const LandCal& land);
    void expectLandRevnue(const LandCal& landCal);
    int getAssementStandardTaxBase(LandTaxCal landTaxCal, double standardTaxBase);
    const int getNumofHoouses() const {   return numoofHouse_; }
    std::shared_ptr<LandTaxCal> makeLandInfo();
private:
    int numoofHouse_;
};