#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N,S;
vector<int> num;
int cache[1001][101];

int sol(int from, int parts)
{
    int& ret = cache[from][parts];
    if(ret != -1) return ret;
    
}

int main()
{
    int tc;
    cin >>tc;

    while(--tc){
        cin >> N >> S;
        for(int i=0; i< N ; ++i){
            int tmp;
            num.push_back(tmp);
        }
        sort(num.begin(), num.end();
        
    }
    return 0;
}