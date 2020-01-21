/**************************************************************
    Problem: 1828
    User: akachoochoo
    Language: C++
    Result: Success
    Time:1 ms
    Memory:2244 kb
****************************************************************/
 
 
// http://jungol.co.kr/bbs/board.php?bo_table=pbank&wr_id=1101&sca=3050
// 1828 : 냉장고, Greedy
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;
 
#define MAX_N 101
 
int N;
vector<pair<int,int>> Cn;
int x, y;
int ans;
 
int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
 
    cin >> N;
 
    for(int i=1; i<=N; i++){
        cin >> x >> y;
        Cn.push_back(make_pair(x,y));
    }
 
    sort(Cn.begin(), Cn.end());
 
    int temp_curr = Cn[0].first;
    int temp_low = Cn[0].first;
    int temp_high = Cn[0].second;
    ans = 1;
     
    for(int i=1; i<N; i++)
    {
        // cout << Cn[i].first << ", " << Cn[i].second;
        // check temp for nex_sample
        if(Cn[i].first > temp_curr){
            // check temp for prev_sample
            if(Cn[i].first > temp_high){
                // chage chamber
                ans++;
                temp_curr = Cn[i].first;
                temp_low = Cn[i].first;
                temp_high = Cn[i].second;
                // cout << "  change Chamber!!" << endl;
            }
            else{
                temp_curr = Cn[i].first;
                if(temp_high > Cn[i].second) temp_high = Cn[i].second;
                // cout << "  change temp. high : " << temp_curr << endl;
            }
        }
    }
 
    cout << ans;
 
    return 0;
}