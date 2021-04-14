#include <iostream>

using namespace std;

int countCache[100][100];
int n;

int cache2[100][100];

int path2(int y, int x)
{
    if(y == n-1)    return cache2[y][x];

    int& ret = cache2[y][x];
    if(ret != -1)   return ret;
    return ret = max(path2(y+1,x), path2(y+1, x+1)) + cache2[y][x];
}

int count(int y, int x)
{
    if(y == n -1)   return 1;

    int& ret = countCache[y][x];
    if(ret != -1)   return ret;
    ret = 0;

    if((y+1, x) >= path2(y+1, x+1))   ret += count(y+1, x);
    if(path2(y+1, x) <= path2(y+1, x+1))   ret += count(y+1, x+1);

    return ret;
}

int main()
{
    return 0;
}