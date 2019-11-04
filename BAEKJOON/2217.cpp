#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector <int>rope_list;


int main(void){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int N, rope;
    cin >> N;
    for(int i=0; i<N; i++){
        cin >> rope;
        rope_list.push_back(rope);
    }
    
    sort(rope_list.begin(), rope_list.end());

    int max_wieght = -1;
    for(int i=0; i<rope_list.size(); i++)
    {
        if(rope_list.at(i)*N > max_wieght)
            max_wieght = rope_list.at(i)*N;
        N -= 1;
    }

    cout << max_wieght;

    return 0;
}