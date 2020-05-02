#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int areFriend[10][10];
int N, M;

void input()
{
    memset(areFriend, 0, sizeof(areFriend));

    cin >> N >> M;
    for(int i=0; i < M; i++) {
        int a , b;
        cin >> a >> b;
        areFriend[a][b] = areFriend[b][a] = 1;
     }
}

int countPairs(bool cache[10])
{
    int ret = 0;
    int firstFree = -1;
    for(int i=0; i<N ; i++) {
        if(!cache[i])   firstFree = i;  break;
    }

    if(firstFree == -1) return 1;

    for(int pairWith = firstFree + 1; pairWith < N; pairWith++) {
        if(!cache[pairWith] && areFriend[firstFree][pairWith]) {
            cache[pairWith] = cache[firstFree] = true;
            ret += countPairs(cache);
            cache[pairWith] = cache[firstFree] = false;
        }
    }
    return ret;
}

int main()
{
    int tc;
    cin >> tc;

    while(tc--)
    {
        bool cache[10];
        input();
        cout << countPairs(cache) << endl;
    }
    return 0;
}