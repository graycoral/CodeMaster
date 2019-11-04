#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector <int>minutes;

int main(void){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int N, minute;
    cin >> N;

    for(int i=0; i<N; i++){
        cin >> minute;
        minutes.push_back(minute);
    }

    sort(minutes.begin(), minutes.end());

    vector <int>::iterator iter;

    int curr_t = 0;
    int ans = 0;

    for(iter=minutes.begin(); iter!=minutes.end(); iter++){
        curr_t += *iter;
        ans += curr_t;
    }

    cout << ans;

    return 0;
}