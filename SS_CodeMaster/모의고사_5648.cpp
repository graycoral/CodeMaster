#include <iostream>
#include <cstring>

#define MAX(a, b) (a > b ? a : b)
using namespace std;

constexpr int maxn = 1000+10;
struct pos {
    int r, c;
    int dic;
    int val;
};

struct DP {
    int preIdx;
    int len;
};

struct pos atom[maxn];
struct DP dp[maxn];
int cnt;


void getData()
{
    memset(atom, 0, sizeof(atom));
    memset(dp, -1, sizeof(dp));
    cnt = 0;

    int N;
    cin >> N;
    for(int i=0; i<N; i++) {
        cin >> atom[i].r;
        cin >> atom[i].c;
        cin >> atom[i].dic;
        cin >> atom[i].val;
    }
}

int checkMeet(int idx)
{
    int retVal = 0;
    return retVal;
}

void sol(int tc)
{
    int N;

    int engerySum = 0;
    memset(dp, -1, sizeof(dp));

    cin >> N;

    // check position
    for(int i=0; i<N; i++) {
        int tmplen = checkMeet(i);
        if(dp[i].len > tmplen) {
            dp[i].len = MAX(dp[i].len, checkMeet(i));
        }
    }

    for(int i=0; i<N; i++){
        if(dp[i].len != -1) {
            engerySum += atom[i].val;
        }
    }

    cout << "#" << tc << " " << engerySum << endl;
}

int main()
{
    int t;
    cin >> t;

    for(int i= 0; i<t; i++) {
        getData();
        sol(i);
    }
    return 0;
}