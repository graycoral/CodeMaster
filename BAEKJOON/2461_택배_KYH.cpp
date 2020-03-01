#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

const int MAXN = 1e4+1;
vector<pair<pair<int,int>, int>> boxs;
int sum[MAXN];
int N,C;

int cmp(const pair<pair<int,int>, int>& rhs, const pair<pair<int,int>, int>& lhs)
{
    if(rhs.first.second == lhs.first.second) {
        return rhs.first.first < lhs.first.first;
    }
    return rhs.first.second < lhs.first.second;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int m;
    cin >> N >> C;
    cin >> m;

    for(int i=0; i < m; ++i){
        int s, e, w;
        cin >> s >> e >> w;
        boxs.push_back(make_pair(make_pair(s,e), w));
    }
    sort(boxs.begin(), boxs.end(), cmp);

    int tCnt = 0;

    for(int i=0; i< m; ++i) {
        auto& box = boxs[i];
        int tmpW = 0, addW = 0;
        for(int pos = box.first.first; pos <= box.first.second; pos++ ) {
            if(sum[pos] > tmpW ) { tmpW = sum[pos]; }
        }
        if(tmpW + box.second > C)   addW = C - tmpW;
        else addW = box.second;

        for(int pos = box.first.first; pos < box.first.second; pos++ ) {
            sum[pos] += addW;
        }

        tCnt += addW;
    }

    cout << tCnt << endl;


    return 0;
}