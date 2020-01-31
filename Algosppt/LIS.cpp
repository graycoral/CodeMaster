#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

#define MAXN	((int)5e2+10)
using namespace std;
int tc;
int N;
int dp[MAXN];
vector<int> numList;

int lis(int s)
{
    int& ret = dp[s];

    if(ret != -1)   return ret;
    ret = 1;

    for(int i = s+ 1; i<N; ++i){
        if(numList[s] < numList[i]) {
            ret = max(ret, 1 + lis(i));
        }
    }

    return ret;
}

int main()
{
    cin >> tc;
    while(tc--){
        cin >> N;
        numList.clear();
        for(int i=0;i<N; i++){
            int tmp;
            cin >> tmp;
            numList.push_back(tmp);
        }
        memset(dp, -1, sizeof(dp));
        int maxlen = 0;
        for(int i=0; i <N; ++i){
            maxlen = max(maxlen , lis(i));
        }
        cout << maxlen << endl;
    }

    return 0;
}