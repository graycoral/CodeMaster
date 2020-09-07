#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>
#include <sstream>

#include <LandTaxCal.h>
#include "landConfigurartion/LandConfigurartion.h"

#ifdef __linux__
 #define clrscr()    system("clear")
#endif

#ifndef __linux__
 #define clrscr()    system("cls")
#endif

using namespace std;

static const string kJsonPath = "./etc/landinfo.json";

class LandCal
{
    vector<std::shared_ptr<LandTaxCal>> landTaxCal;
public:
    LandCal() : readJson(kJsonPath, numoofHouse_, name_) { }
    void init();
    int readData();
    void showMain();
    void calTax(std::shared_ptr<LandTaxCal> landTaxCal);
    void saveDatatoExcel();
    void addLandInfo(int idx, bool database);
    void updateLandInfo();
    void showLandInfo();
    void expectLandRevnue(const LandCal& landCal);
    int getAssementStandardTaxBase(LandTaxCal landTaxCal, double standardTaxBase);
    const int getNumofHoouses() const {   return numoofHouse_; }
    int increaseNumofHouse() {  return ++numoofHouse_;}
    std::shared_ptr<LandTaxCal> makeLandInfo(int num, bool database);
private:
    int numoofHouse_;
    string name_;
    LandConfiguration readJson;
};