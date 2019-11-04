#include <iostream>
#include <vector>
using namespace std;

vector <int> coinVec;

int main(void){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int N, K;
    int coin;
    cin >> N >> K;
    
    for(int i=0; i<N; i++){
        cin >> coin;
        coinVec.push_back(coin);
    }

    int MinCoinCount = 0;

    for(int i = coinVec.size()-1; i>=0; i--){
        while(K >= coinVec.at(i)){
            K -= coinVec.at(i);
            MinCoinCount++;
        }
    }

    cout << MinCoinCount;
    
    return 0;
}