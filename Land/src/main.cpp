#include "../inc/LandCal.h"

using namespace std;

#define clrscr()    system("cls")

int main(int argc, const char* argv[])
{
    int cmd;    
	LandCal land;

    while(1) {
        clrscr();
        cout << "========== Land Calculator ==========" << endl;
		land.showMain();
        cin >> cmd;
        if(cmd == 1) {
			clrscr();
            land.addLandInfo();
        } else if (cmd == 2) {
			clrscr();
            land.saveDatatoExcel();
        } else if (cmd == 3) {
			clrscr();
            land.updateLandInfo();
		}
		else if (cmd == 4) {
			clrscr();
			land.showLandInfo(land);
		}
		else if (cmd == 5) {
			clrscr();
			land.showLandInfo(land);		
		} else if (cmd == 6) {
			cout << " Exit Land Calculator " << endl;
			exit(0);
		}
		else {
			cout << " Invalid Command" << endl;
			continue;
		}
    }
}