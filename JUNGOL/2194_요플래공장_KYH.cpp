#include <iostream>

using namespace std;

int main()
{
    int N, S;
    long long int cost = 0xffff, sum = 0;

    cin >> N >> S;

    for(int i=0; i<N; i++){
        long long int c,y;
        cin >> c >> y;
        if(cost + S > c) {
            cost = c;
        } else {
            cost += S;
        }
        sum += cost * y;
    }

    cout << sum;

    return 0;
}