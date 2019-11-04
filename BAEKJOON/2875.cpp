#include <iostream>
using namespace std;

int main(void){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int N,M,K;
    // woman, man, internship
    cin >> N >> M >> K;

    int maxTeam = N/2;

    while( maxTeam > 0){
        if((M-maxTeam)+(N-maxTeam*2)>=K && maxTeam<=M) break;
        maxTeam--;
    }

    cout << maxTeam;
    
    return 0;
}
