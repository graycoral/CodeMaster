// https://www.acmicpc.net/problem/2565
// 2565 : 전깃줄, LIS
#include <iostream>
#include <utility>
#include <algorithm>
#include <vector>

using namespace std;
 
int N;
int x, y;
vector<pair<int, int>> input;
vector<int> lis (1, -1);

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;

    for(int i=0; i<N; i++)
    {
        cin >> x >> y;
        input.push_back({x,y});
    }

    sort(input.begin(), input.end());
    
    for(auto p : input){
        if(p.second > lis.back()){
            lis.push_back(p.second);
        }
        else
        {
            auto it = lower_bound(lis.begin(), lis.end(), p.second);
            *it = p.second;
        }
    }

    cout << N - (lis.size()-1) << endl;

    return 0;
}