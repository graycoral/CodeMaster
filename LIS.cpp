#include <iostream>
#include <string.h>
#include <algorithm>
#include <iterator>
#include <vector>
#include <utility>

using namespace std; 

bool comp(const pair<int,int> &a, const pair<int,int> &b){
    return a.first < b.first;
}

int main(void){
    int max = 0;
    int dp[100];

////////////////////////////////////////////////////////// LIS : O(N^2)
    int arr1[6] = {10,20,10,30,20,50};

    dp[0] = 1;

    for(int i=1; i<6; i++){
        dp[i] = 1;
        for(int j=0; j<i; j++){
            if(arr1[i]>arr1[j] && dp[j]+1>dp[i])
            {
                dp[i] = dp[j]+1;
            }
        }
        if(max < dp[i]) max=dp[i];
    }
    printf("LIS : %d\n",max);

////////////////////////////////////////////////////////
    int arr2[10] = {1, 100, 2, 50, 60, 3, 5, 6, 7, 8};
    
    memset(dp,0,sizeof(dp));

    dp[0] = arr2[0];
    int temp = 0;
    for(int i=1; i<10; i++){
        for(int j=0; j<i; j++){
            if(arr2[i]>arr2[j] && dp[j]+arr2[i]>dp[i])
            {
                dp[i] = dp[j] + arr2[i];
            }
        }
        if(max < dp[i]) max=dp[i];
    }

    for(int i=0; i<10; i++)
    {
        cout << dp[i] << ", ";
    }

    printf("max sum : %d\n", max);

////////////////////////////////////////////////////////// LIS : O(NlgN)
    vector<int> lis (1, -1);

    for(int i=0; i<6; i++)
    {
        if(lis.back() < arr1[i]){
            lis.push_back(arr1[i]);
        }
        else{
            auto it = lower_bound(lis.begin(), lis.end(), arr1[i]);
            *it = arr1[i];
        }
    }

    printf("lis size : %d\n", lis.size()-1);

////////////////////////////////////////////////////////// LIS : O(NlgN) with backtracking
    vector<pair<int,int>> inp;  
    vector<pair<int,int>> ans (1, {-1,-1});
    vector<int> backtracking (6+1,-1);
    vector<int> lis2;

    for(int i=0; i<6; i++){
        inp.push_back({arr1[i],i});
    }

    for(auto p : inp){
        if(ans.back().first < p.first){
            backtracking[p.second] = ans.back().second;
            ans.push_back(p);
        }
        else{
            auto it = lower_bound(ans.begin(), ans.end(), p, comp);
            backtracking[p.second] = (it-1)->second;
            
            *it = p;
        }
    }

    for(int cur=ans.back().second; cur>=0; cur=backtracking[cur]){
        lis2.push_back(inp[cur].first);
    }
    reverse(lis2.begin(), lis2.end());
    
    printf("\nlis size : %d\n", lis.size()-1);

    return 0;
}