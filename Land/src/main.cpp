#include <iostream>

using namespace std;

#include "../inc/Land.h"
#include "../inc/LandTaxCal.h"

#define clrscr()    system("cls")

int main(int argc, const char* argv[])
{
    int cmd;
    cout << "========== Hello Land Tax Calculator ==========" << endl;
    Land land;
    while(1) {
        clrscr();
        land.showMain();
        cin >> cmd;
        if(cmd == 1) {
            land.addLandInfo();
        } else if (cmd == 2) {
            land.

        } else if (cmd == 3) {

        } else if (cmd == 4) {

        }
    }
}