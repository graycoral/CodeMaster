/**************************************************************
    Problem: 1831
    User: akachoochoo
    Language: C++
    Result: Success
    Time:6 ms
    Memory:4852 kb
****************************************************************/
 
 
// http://www.jungol.co.kr/bbs/board.php?bo_table=pbank&wr_id=1104&sca=30
// Divide and Conquer
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
 
#define MAX 100001
 
int N, T, L;
vector <int> table[MAX+1];
int ans;
 
void solve(){
    int start_time = MAX;
    for(int idx=MAX-1; idx>=0; idx--){
        if(table[idx].size() > 0)
        {   
            sort(table[idx].begin(), table[idx].end());
            if(idx + table[idx][0] <= start_time)
            {
                start_time = idx;
                // cout << idx << ", "; 
                ans++;
                // cout << idx+table[idx][0] << " : " << ans << endl;
            }
        }
    }
}
 
int main(void){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
 
    cin >> N;
 
    for(int i=1; i<=N; i++){
        cin >> T >> L;
        table[T].push_back(L);
    }
     
    solve();
 
    cout << ans << endl;
 
    return 0;
}