#include <iostream>

using namespace std;

#include "../inc/Land.h"

#define clrscr()    system("cls")

int main(int argc, const char* argv[])
{
    int cmd;
    cout << "========== Hello Land Tax Calculator ==========" << endl;
    Land land;
    while(1) {
        clrscr();
        cout << "========== Land Calculator ==========" << endl;
        cin >> cmd;
        if(cmd == 1) {
            land.addLandInfo();
        } else if (cmd == 2) {
            // land.calTax();
        } else if (cmd == 3) {
            // land.saveDatatoExcel();
        } else if (cmd == 4) {
            // land.updateLandInfo();
        }
    }
}