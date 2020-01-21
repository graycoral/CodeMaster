// http://www.jungol.co.kr/bbs/board.php?bo_table=pbank&wr_id=684&sca=3070
// 1408 : 전기줄(초), DP, LIS
#include <iostream>
#include <utility>
#include <algorithm>
#include <vector>

using namespace std;

#define MAX_N 101
#define MAX_H 501
 
int N;
int x, y;
vector<pair<int, int>> arr;
int dp[MAX_N];

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;

    for(int i=1; i<=N; i++)
    {
        cin >> x >> y;
        arr.push_back(make_pair(x,y));
    }

    sort(arr.begin(), arr.end());

    dp[0] = 1;
    
    int max = 0;
    for(int i=1; i<=N; i++){
        dp[i] = 1;
        for(int j=0; j<i; j++){
            if(arr[i].second > arr[j].second && dp[j]+1>dp[i])
            {
                dp[i] = dp[j]+1;
            }
        }
        if(max < dp[i])
            max = dp[i];
    }

    cout << endl;
    
    cout << N-max;

    return 0;
}