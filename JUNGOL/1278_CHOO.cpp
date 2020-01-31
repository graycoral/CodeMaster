// http://www.jungol.co.kr/bbs/board.php?bo_table=pbank&wr_id=561&sca=99&sfl=wr_subject&stx=%EB%B0%B0%EB%82%AD
// 1278 : 배낭채우기2, DP
#include <iostream>
#include <algorithm>

#define MAX_W 10001
#define MAX_N 1000

using namespace std;

int N, W;
int Wi[MAX_N];
int Pi[MAX_N];
int dp[MAX_W];
int dp_2d[MAX_N+1][MAX_W];

void solve(){
    for(int i=0; i<N; i++){
        for(int j=W; j>=Wi[i]; j--){
            dp[j] = max(dp[j-Wi[i]]+Pi[i], dp[j]);
        }
    }
    cout << dp[W] << endl;
}

void solve2(){
    for(int i=1; i<=N; i++){
        for(int j=1; j<=W; j++){
            // 이전 값을 사용
            if(j-Wi[i-1] < 0){
                dp_2d[i][j] = dp_2d[i-1][j];
            }
            else{
                dp_2d[i][j] = max(dp_2d[i-1][j-Wi[i-1]]+Pi[i-1], dp_2d[i-1][j]);
            }
        }
    }
    cout << dp_2d[N][W] << endl;
}

int main(void){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    // for(int i=0; i<N; i++) dp[i] = 0;

    cin >> N >> W;
    for(int i=0; i<N; i++){
        cin >> Wi[i] >> Pi[i];
    }

    solve();
    
    solve2();

    return 0;
}
