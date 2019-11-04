#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector <int> dp;

int f(int n){
    if(n==1) return 0;
    if(dp[n] != -1) return dp[n];

    int result = f(n-1) + 1;
    if(n%3 == 0) result = min(result, f(n/3)+1);
    if(n%2 == 0) result = min(result, f(n/2)+1);
    dp[n] = result;
    return result;
}

int main(void){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int N;
    cin >> N;
    dp.resize(N+1, -1);
    cout << f(N);

    return 0;
}