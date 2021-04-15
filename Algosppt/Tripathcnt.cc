#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int countCache[100][100];
int map[100][100];
int ans;
int T;
int n;

int cache2[100][100];

int path2(int y, int x)
{
    if(y == n-1)    return map[y][x];

    int& ret = cache2[y][x];
    if(ret != -1)   return ret;
    return ret = max(path2(y+1,x), path2(y+1, x+1)) + map[y][x];
}

int count(int y, int x)
{
    if(y == n -1)   return 1;

    int& ret = countCache[y][x];
    if(ret != -1)   return ret;
    ret = 0;

    if(path2(y+1, x) >= path2(y+1, x+1))   ret += count(y+1, x);
    if(path2(y+1, x) <= path2(y+1, x+1))   ret += count(y+1, x+1);

    return ret;
}

void init()
{
    memset(cache2, -1, sizeof(cache2));
	memset(map, -1, sizeof(map));
	memset(countCache, -1, sizeof(countCache));
}

void input()
{
    cin >> n;
    for(int r = 0; r < n; r++) {
        for(int c = 0; c <= r; c++) {
            cin >> map[r][c];
        }
    }
}
int main()
{
    int t;
    cin >> t;
    for(int i=0; i<t; i++) {
        ans = 0;
        init();
        input();
        ans = count(0,0);
        cout << ans << endl;
    }
    return 0;
}