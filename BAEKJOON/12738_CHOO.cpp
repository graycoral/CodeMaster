// https://www.acmicpc.net/problem/12738
// 12738 : 가장 긴 증가하는 부분 수열 3, LIS
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

long long int N;
long long int temp;
vector<long long int> lis;

int main(void){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;

    cin >> temp;
    lis.push_back(temp);

    for(long long int i=1; i<N; i++){
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

    cout << lis.size();

    return 0;
}