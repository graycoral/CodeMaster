#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>

#include <LandTaxCal.h>
#ifdef __linux__
#define clrscr()    system("clear")
#endif

#ifndef __linux__
#define clrscr()    system("cls")
#endif

using namespace std;

class LandCal
{
    vector<std::shared_ptr<LandTaxCal>> landTaxCal;
public:
    LandCal() : numoofHouse_(0) {}
    void init();
    int readData();
    void showMain();
    void addLandInfo();
    void addLandInfofromData(int idx);
    void calTax(std::shared_ptr<LandTaxCal> landTaxCal);
    void saveDatatoExcel();
    void updateLandInfo();
    void showLandInfo();
    void expectLandRevnue(const LandCal& landCal);
    int getAssementStandardTaxBase(LandTaxCal landTaxCal, double standardTaxBase);
    const int getNumofHoouses() const {   return numoofHouse_; }
    std::shared_ptr<LandTaxCal> makeLandInfo(int num);
private:
    int numoofHouse_;
    string name_;
};