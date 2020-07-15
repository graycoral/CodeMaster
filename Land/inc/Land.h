#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "../inc/LandCal.h"

using namespace std;

class Land
{
    vector<LandCal*> landCal;
public:
    Land() : numoofHouse_(0) {}
    void command();
    void showMain();
    void addLandInfo();
    LandCal makeLandInfo();
private:
    int numoofHouse_;
};