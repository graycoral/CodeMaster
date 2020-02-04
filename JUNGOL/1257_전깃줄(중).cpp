#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
const int MAXN = 1e6+10;

int N;
vector<int> path;
vector<pair<int,int>> Line;
int D[MAXN];
int P[MAXN];

void input()
{
    cin >> N;
    for(int i=0; i<N;i++){
        int tmp1, tmp2;
        cin >> tmp1 >> tmp2;
        Line.push_back(make_pair(tmp1, tmp2));
    }
}

int BS(int s, int e, int v)
{
    int ret = 0;
    while(s<=e){
        int m = (s+e)/2;
        if(Line[D[m]].second < v) {
            s = m +1;
            ret = s;
        } else {
            e = m -1;
        }
    }
    return ret;
}

void sol()
{
    int cur = 0;

    sort(Line.begin(), Line.end());
    for(int i=0; i<N; i++){
        int idx = BS(0, cur, Line[i].second);
        if(idx <= cur){
            if(Line[D[idx]].second > Line[i].second) {
                D[idx] = i;
                P[i] = D[idx-1];
            }
        }
        else {
            P[i] = D[cur];
            D[cur++] = i;
        }
    }
    cout << cur << endl;
    for(int i=0;i < cur ; i++){
        cout << Line[D[i]].second << endl;
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    input();
    sol();
    return 0;
}