#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector <pair<int,int>> candidates;
int ans;

int main(void){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T, N;
    int paper, interview;
    int min = 100000;
    cin >> T;

    while(T--){
        cin >> N;
        ans = 0; 
        min = 100000;

        for(int i=0; i<N; i++){
            cin >> paper >> interview;
            candidates.push_back(make_pair(paper, interview));
        }

        sort(candidates.begin(), candidates.end());

        vector <pair<int, int>>::iterator it;
        
        for(it=candidates.begin(); it!=candidates.end(); it++)
        {
            if(it->second <= min)
            {
                min = it->second;
                ans++;
            }
        }

        candidates.clear();
        cout << ans << endl;
    }

    return 0;
}