// https://www.acmicpc.net/submit/11053
// https://www.acmicpc.net/problem/12015
// 11053 : 가장 긴 증가하는 부분 수열, LIS O(N^2) 이 목표로 보임
// 12015 : 가장 긴 증가하는 부분 수열 2, LIS O(NlgN) 이 목표로 보임
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

#define MAX_N 1001
int N;
int temp;
vector<int> lis (1, -1);

int main(void){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;

    for(int i=0; i<N; i++){
        cin >> temp;
        if(temp>lis.back()){
            lis.push_back(temp);
        }
        else
        {
            auto it = lower_bound(lis.begin(), lis.end(), temp);
            *it = temp;
        }
    }

    cout << lis.size()-1;

    return 0;
}