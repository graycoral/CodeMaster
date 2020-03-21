#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

void sol()
{
    string a;
    int b;
    bool first = false; // true : black
    bool second = false;

    cin >> a >> b;

    int aS = a[0] - 'A' + 1;
    int bS = a[1];
    if(aS % 2 == bS % 2) first = true;
    if(((b-1)/8 + 1) % 2 == (b%8)%2) second = true;
    if(first == second) cout << "YES" << endl;
    else cout <<"NO" << endl;

}

int main()
{
    int tc;
    cin >> tc;
    while(tc--) {
        sol();
    }
}