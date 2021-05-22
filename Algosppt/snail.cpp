#include <iostream>
#include <cstring>

using namespace std;

const int maxn = 1000 + 10;
int n, m;
int cache[maxn][maxn];
int ans;
int T;

int climb(int days, int climbed)
{
    if(days == m) return climbed >= n ? 1 : 0;
    int& ret = cache[days][climbed];

    if(ret != -1) return ret;

    return ret = climb(days+1, climbed + 1) + climb(days+1, climbed + 2);
}

int main()
{
    cin >> T;
    for(int i=0; i<T; i++) {
        ans = 0;
        memset(cache, 0, sizeof(cache));
        cin >> n;
        ans = climb(0, 0);
        cout << ans << endl;
    }
    return 0;
}