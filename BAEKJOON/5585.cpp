#include <iostream>
#include <vector>
using namespace std;

vector <int> coinVec = {500, 100, 50, 10, 5, 1};

int main(void){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int Money;
    int coin = 0;
    cin >> Money;
    Money = 1000 - Money;
    
    for(int i=0; i<coinVec.size(); i++){
        while(Money >= coinVec.at(i)){
            Money -= coinVec.at(i);
            coin++;
        }
    }

    cout << coin;
    
    return 0;
}