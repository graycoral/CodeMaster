// https://www.acmicpc.net/problem/14002
// 가장 긴 증가하는 부분 수열 4, LIS O(NlgN) with backtracking

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <utility>
using namespace std;

#define MAX_N 1001

int N;
int temp;
vector<pair<int,int>> input;
vector<pair<int,int>> ans (1, {-1,-1});
vector<int> lis;
vector<int> backtracking (MAX_N, -1);

bool comp(const pair<int,int> &a, const pair<int,int> &b){
    return a.first < b.first;
}

int main(void){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;

    for(int i=0; i<N; i++){
        cin >> temp;
        input.push_back({temp, i});
    }

    for(auto p : input){
        if(p.first > ans.back().first){
            backtracking[p.second] = ans.back().second;
            ans.push_back(p);
        }
        else{
            auto it = lower_bound(ans.begin(), ans.end(), p, comp);
            backtracking[p.second] = (it-1)->second;
            *it = p;
        }
    }

    for(int cur = ans.back().second; cur>=0; cur=backtracking[cur])
        lis.push_back(input[cur].first);

    cout << lis.size() << endl;

    reverse(lis.begin(), lis.end());

    for(auto v : lis){
        printf("%d ", v);
    }

    return 0;
}