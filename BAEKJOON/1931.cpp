#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

vector <pair<int,int>> time_vec;

int main(void){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int N;
    int S, E;
    cin >> N;

    for(int i=0; i<N; i++){
        cin >> S >> E;
        time_vec.push_back(make_pair(E, S));
    }

    sort(time_vec.begin(), time_vec.end());

    int end_time = -1;
    int count = 0;

    vector<pair<int,int>>::iterator iter;
    for(iter = time_vec.begin(); iter != time_vec.end(); iter++){
        if(iter->second >= end_time)
        {
            end_time = iter->first;
            count++;
        }
    }

    cout << count;

    return 0;
}