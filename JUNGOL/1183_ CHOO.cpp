/**************************************************************
    Problem: 1183
    User: akachoochoo
    Language: C++
    Result: Success
    Time:1 ms
    Memory:2240 kb
****************************************************************/
 
 
// http://www.jungol.co.kr/bbs/board.php?bo_table=pbank&wr_id=466&sca=30
// Divide and Conquer
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
 
#define COIN_NUM 6 // 500, 100, 50, 10, 5, 1
 
int W, _max;
int coin_list[6] = {500, 100, 50, 10, 5, 1};
int coins_held[6];
// int coins_used[6];
int ans;
 
void solve(){
    int remain = _max - W;
    int index = 0;
    while(true){
        if(remain <= 0 || index>=COIN_NUM) break;
        if(remain >= coin_list[index] &&  coins_held[index]>0){
            remain -= coin_list[index];
            coins_held[index]--;
            ans--;
        }
        else
        {
            index++;
        }
    }
}
 
int main(void){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
 
    cin >> W;
    _max = 0;
     
    for(int i=0; i<COIN_NUM; i++){
        cin >> coins_held[i];
        _max += coin_list[i]*coins_held[i];
        ans += coins_held[i];
    }
 
     
    solve();
 
    cout << ans << endl;
 
    for(int i=0; i<COIN_NUM; i++){
        printf("%d ",coins_held[i]);
    }
 
    return 0;
}