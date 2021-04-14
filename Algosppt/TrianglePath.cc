#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int map[100][100];
int dp[100][100];
int ans;
int T;
int N;

int sol()
{
    for(int r = 0; r < N; r++) {
        for(int c = 0; c <= r; c++) {
            cin >> map[r][c];
        }
    }

    dp[0][0] = map[0][0];
    for(int r = 1; r < N; r++) {
        for(int c = 0; c <= r; c++) {
            if( c == 0)  {
                dp[r][c] = dp[r-1][c] + map[r][c];
            }
            else {
                dp[r][c] = map[r][c] + max(dp[r-1][c],  dp[r-1][c-1]);
            }
        }
    }

    for(int i = 0; i<T; i++) {
        if(ans < dp[N-1][i])    ans = dp[N-1][i];
    }

    return ans;
}

int n, triangle[100][100];
int cache[100][100][100*100+1];

int path1(int y, int x, int sum)
{
    if(y == N-1)    return sum + map[y][x];
    int& ret = cache[y][x][sum];
    if(ret != -1)   return ret;

    sum += map[y][x];

    return ret = max(path1(y+1, x+1, sum), path1(y+1, x, sum));
}

int cache2[100][100];

int path2(int y, int x)
{
    if(y == N-1)    return map[y][x];

    int& ret = cache2[y][x];
    if(ret != -1)   return ret;
    return ret = max(path2(y+1,x), path2(y+1, x+1)) + map[y][x];
}

void init()
{
    memset(cache2, -1, sizeof(cache2));
}
int main()
{
    cin >> T;
    for(int i=0; i<T; i++) {
        ans = 0;
        cin >> N;
        // ans = sol();
        ans = path2(0,0);
        cout << ans << endl;
    }

    return 0;
}