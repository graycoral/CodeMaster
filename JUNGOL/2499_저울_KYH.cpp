#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
const int MAXN = 1e3+10;

vector<int> Data;
int dp[MAXN];
int N;

void rec(int idx, int n)
{
    for(int i=idx; i<N; i++){
        if(dp[i] > 0)   continue;
    }
}

int main()
{
    cin >> N;
    for(int i=0; i <N; i++){
        int tmp;
        cin >> tmp;
        Data.push_back(tmp);
    }
    sort(Data.begin(), Data.end());



    return 0;
}