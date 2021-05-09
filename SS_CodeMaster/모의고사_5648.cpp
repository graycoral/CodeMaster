#include <iostream>
#include <cstring>

#define MAX(a, b) (a > b ? a : b)
using namespace std;

constexpr int maxn = 1000+10;
typedef struct pos {
    int r, c;
    int dic;
    int val;
    int alive;
}Pos ;

Pos atom[maxn];
int N;
int totalCnt;


void getData()
{
    memset(atom, 0, sizeof(atom));

    int N;
    cin >> N;
    for(int i=0; i<N; i++) {
        cin >> atom[i].r;
        cin >> atom[i].c;
        cin >> atom[i].dic;
        cin >> atom[i].val;

        atom[i].r += 1000;
        atom[i].c += 1000;
        atom[i].alive = 1;
    }
    totalCnt = N;
}

int checkMeet()
{
    int retVal = 0;
    int aliveFlag = 0;
    for(int i = 0; i<N; i++) {
        if(totalCnt == 0)   return retVal;
        for(int j = i+1; j<N; j++) {
            if(atom[j].alive == 0)  continue;
            if(atom[i].r == atom[j].r && atom[i].c == atom[j].c) {
                retVal += atom[i].val;
                retVal += atom[j].val;
                atom[j].alive = 0;
                aliveFlag = 1;
                totalCnt--;
            }
        }
        if(aliveFlag == 1){
            atom[i].alive = 0;
            totalCnt--;
        }
        aliveFlag = 0;
    }
    return retVal;
}

void sol(int tc)
{
    int engerySum = 0;
    cin >> N;

    // check position
    for(int i=0; i<2000; i++) {
        for(int j = 0; j<N; j++) {
            if(atom[j].alive == 0)  continue;
            if(atom[j].dic == 0 )       atom[j].r--;
            else if(atom[j].dic == 1 )  atom[j].r++;
            else if(atom[j].dic == 2 )  atom[j].c--;
            else if(atom[j].dic == 3 )  atom[j].c++;
        }
        engerySum += checkMeet();
    }

    cout << "#" << tc << " " << engerySum << endl;
}

int main()
{
    int t;
    cin >> t;

    for(int i= 1; i<=t; i++) {
        getData();
        sol(i);
    }
    return 0;
}