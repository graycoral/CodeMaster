// http://www.jungol.co.kr/bbs/board.php?bo_table=pbank&wr_id=1273&sca=99&sfl=wr_subject&stx=%EB%8F%99%EC%A0%84%EA%B5%90%ED%99%98
// 2000 : 동전교환, DP
#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>

#define MAX_W   ((int)64001)
#define INF		((int)0x7ffffff)

using namespace std;

int N, W;
vector<int> coins;
int dp[MAX_W];

int main(void){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    for(int i=0; i<MAX_W; i++) dp[i] = INF;

    cin >> N;
    for(int i=0; i<N; i++){
        int temp;
        cin >> temp;
        coins.push_back(temp);
    }

    cin >> W;

    dp[0] = 0;
    for(int i=0; i<N; i++){
        for(int j=coins[i]; j<=W; j++){
            // if(dp[j] == -1 )
            //     dp[j] = dp[j-coins[i]]+1;
            // else
                dp[j] = min(dp[j-coins[i]]+1, dp[j]);
        }
    }

    if(dp[W] == INF) cout << "impossible" << endl;
    else cout << dp[W] << endl;
}

