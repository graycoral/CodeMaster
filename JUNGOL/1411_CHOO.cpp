/**************************************************************
    Problem: 1411
    User: akachoochoo
    Language: C++
    Result: Success
    Time:2 ms
    Memory:3024 kb
****************************************************************/
 
 
// http://jungol.co.kr/bbs/board.php?bo_table=pbank&wr_id=687&sca=3060
// 두줄로 타일 깔기 (DP)
#include <iostream>
#include <string.h>
using namespace::std;
 
#define MAX_N 100001
#define DIV 20100529
 
long long int dp[MAX_N];
int N;
 
int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    memset(dp, -1, sizeof(dp));
    cin >> N;
 
    dp[1] = 1;
    dp[2] = 3;
 
    for(int i=3; i<=N; i++)
    {
        dp[i] = (dp[i-1] + dp[i-2]*2)%DIV;
    }
 
    cout << (dp[N]);
 
    return 0;
}