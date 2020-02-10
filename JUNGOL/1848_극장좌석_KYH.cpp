#include <iostream>
#include <vector>

using namespace std;

long long int dp[40+1];

int pivo(int n)
{
    if(dp[n] > 0)   return dp[n];
    dp[n] = pivo(n-1) + pivo(n-2);

    return dp[n];
}

int main()
{
    int N;
    int M;
    vector<int> Seat;

    dp[0] = 1; dp[1] = 1; dp[2] = 2;

    cin >> N;
    cin >> M;

    for(int i=0; i< M; i++){
        int tmp;
        cin >> tmp;
        Seat.push_back(tmp);
    }

    int start = 1;
    long long int sum = 1;

    for(auto S  : Seat){
        sum *= pivo(S - start);
        start = S + 1;
    }

    sum *= pivo(N - start + 1);
    cout << sum;
    return 0;
}