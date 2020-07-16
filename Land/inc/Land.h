#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>

#include "LandTaxCal.h"

using namespace std;

class Land
{
    vector<std::shared_ptr<LandTaxCal>> landCal;
public:
    Land() : numoofHouse_(0) {}
    void showMain();
    void addLandInfo();
    void calTax();
    void saveDatatoExcel();
    void updateLandInfo();
    std::shared_ptr<LandTaxCal> makeLandInfo();
private:
    int numoofHouse_;
};