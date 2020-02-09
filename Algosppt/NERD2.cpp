#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int N;
map<int, int> coord;

bool isDominated(int x, int y)
{
    map<int, int>::iterator it = coord.lower_bound(x);
    if(it == coord.end())   return false;

    return y < it->second;
}

void removeDominated(int x, int y)
{
    map<int, int>::iterator it = coord.lower_bound(x);
    if(it == coord.begin())   return;

    --it;
    while(true)
    {
        if(y < it->second)  break;
        if(it == coord.begin()){
            coord.erase(it);
            break;
        } else {
            auto jt = it;
            --jt;
            coord.erase(it);
            it = jt;
        }
    }
}

int registered(int x, int y)
{
    if(isDominated(x,y))    return coord.size();

    removeDominated(x,y);
    coord[x] = y;
    return coord.size();
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int tc;
    cin >> tc;
    while(tc--){
        int ret = 0;
        cin >> N;
        coord.clear();
        for(int i=0; i<N; i++){
            int x,y;
            cin >> x >> y;
            ret += registered(x,y);
        }
        cout << ret << endl;
    }
    return 0;
}