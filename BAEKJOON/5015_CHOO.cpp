//https://www.acmicpc.net/problem/5015
// 5015 : ls, DP
#include <iostream>
#include <string.h>
#include <string>
#include <vector>

using namespace std;

#define MAX_N 100

string P, F;
vector<string> ans;
int cache[100][100];
int N;

int is_matched(int p, int f){
    int &ret = cache[p][f];

    if(ret != -1) return ret;

    while(p < P.size() && f < F.size() && P[p]==F[f])
        p++, f++;

    if(p==P.size() && f == F.size()) return ret = true;
    
    if(P[p] == '*'){
        for(int skip = 0; f+skip <= F.size(); skip++){
            if(is_matched(p+1,f+skip)) return ret = true;
        }
    }

    return ret = false;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> P;
    cin >> N;
    for(int i=0; i<N; i++){
        cin >> F;
        memset(cache, -1, sizeof(cache));
        if(is_matched(0,0))
            ans.push_back(F);
        F.clear();
    }

    for(auto s : ans)
        cout << s << endl;

    return 0;
}