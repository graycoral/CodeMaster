// https://www.acmicpc.net/problem/2568
// 2568 : 전깃줄 - 2, LIS with backtracking
#include <iostream>
#include <utility>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

#define MAX_N 100000
#define MAX_H 500001
 
int N;
int x, y;
vector<pair<int, int>> input;
vector<pair<int, int>> ans(1,{-1,-1});
vector<int> backtracking(MAX_H, -1);
bool visited[MAX_H];

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;

    for(int i=0; i<N; i++)
    {
        cin >> x >> y;
        input.push_back({x,y});
        visited[x] = true;
    }

    sort(input.begin(), input.end());

    int idx = 0;
    for(auto p : input){
        if(p.second > ans.back().second){
            backtracking[idx] = ans.back().first;
            ans.push_back({idx, p.second});            
        }
        else{
            auto it = lower_bound(ans.begin(), ans.end(), p);
            backtracking[idx] = (it-1)->first;
            *it = {idx, p.second};
        }
        idx++;
    }

    int cnt = 0;
    for(int cur=ans.back().first; cur>=0; cur=backtracking[cur])
    {    
        cnt++;
        visited[input[cur].first] = false;
    }
    
    cnt = N - cnt;
    cout << cnt << endl;

    for(int i=1; i<MAX_H; i++){
        if(cnt == 0) break;
        if(visited[i] == true){
            cout << i << endl;
            cnt--;
        }
    }

    return 0;
}