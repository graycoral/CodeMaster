#include <LandCal.h>

using namespace std;

int main(int argc, const char* argv[])
{
    int cmd;
    LandCal land;
    land.init();

    while(1) {
        // clrscr();
        cout << "========== Land Calculator ==========" << endl;
        land.showMain();
        cin >> cmd;

        if(std::isdigit(cmd) != 0) {
            cout << "please input vaild number" << endl;
        } else if(cmd == 1) {
            land.addLandInfo(land.increaseNumofHouse(), false);
        } else if (cmd == 2) {
            land.saveDatatoExcel();
        } else if (cmd == 3) {
            land.updateLandInfo();
        } else if (cmd == 4) {
            land.showLandInfo();
        } else if (cmd == 5) {
            land.expectLandRevnue(land);
        } else if (cmd == 6) {
            cout << " Exit Land Calculator " << endl;
            clrscr();
            exit(0);
        }
        else {
            cout << " Invalid Command" << endl;
            continue;
        }
    }
}