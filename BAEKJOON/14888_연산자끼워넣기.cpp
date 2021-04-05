#include <iostream>

using namespace std;
const int maxn = 101;

int N;
int num[maxn];
int cal[4];
int total_cnt;


int sol(int num, int calIdx)
{
    if(cal[calIdx] == 0)    return num;
    else return num*cal[calIdx];
}

int main()
{
    freopen("14888_연산자끼워넣기.txt", "r", stdin);
    int T;
    cin >> T;

    for(int i=0; i<T; i++) {
        int tmp;
        cin >> N;
        cin >> tmp;
        num[i] = tmp;
    }

    for(int i=0; i<4; i++){
        int tmpcal;
        cin >> tmpcal;
        cal[i] = tmpcal;
        total_cnt++;
    }

    for(int i=0; i<4; i++) {

    }



    return 0;
}