#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int N;
char Data[6][6];

void input()
{
    for(int i= 0; i<5; i++){
        string tmp;
        cin >> tmp;
        for(int j=0;j <5; j++) {
            Data[i][j] = tmp[j];
        }
    }
}

void sol()
{
    string word;
    int nWord;
    cin >> nWord;
    while(nWord--)
    {
        word.clear();
        cin >> word;
        
    }
    

}

int main()
{
    int tc;
    cin >> tc;
    while(tc--){
        input();
        sol();
    }
}