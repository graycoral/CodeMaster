#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>

const int INF = 987654321;
const int MAXN = 1e4 +1;
using namespace std;

string N;
int cache[MAXN];

int classify(int s, int L) {
    string m = N.substr(s, L);

    if(m == string(m.size(), m[0])) return 1;

    bool prog = true;
    for(int i=0; i<m.size()-1; i++){
        if(m[i+1] - m[i] != m[1] - m[0])   prog = false;
    }
    if(prog && (abs(m[1] - m[0]) == 1))    return 2;

    bool alter = true;
    for(int i=0; i < m.size(); i++){
        if(m[i] != m[i%2])  alter = false;
    }

    if(alter)   return 4;
    if(prog)    return 5;

    return 10;
}

int memoei(int s)
{
    if(s >= N.size())    return 0;
    int& ret = cache[s];
    if(ret != -1)   return ret;

    ret = INF;
    for(int L = 3; L <=5; L++) {
        if(s + L <= N.size()) {
            ret = min(ret, memoei(s + L) +classify(s, L));
        }
    }
    return ret;
}

int main()
{
    int tc;
    cin >> tc;
    while(tc--){
        memset(cache, -1, sizeof(cache));
        N.clear();
        cin >> N;
        cout << memoei(0) << endl;
    }
}