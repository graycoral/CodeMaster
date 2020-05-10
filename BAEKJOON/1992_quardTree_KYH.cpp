#include <iostream>

using namespace std;

char Map[65][65];
int N;

void input()
{
    cin >> N;
    for(int i=0; i<N; i++){
        string tmp;
        cin >> tmp;
        for(int j = 0; j< N; j++){
            Map[i][j] = tmp[j];
        }
    }
}

void decompress(int sr, int sc, int size)
{
    if( sr >= N || sc >= N || size <= 0)    return;

    char prev = Map[sr][sc];
    bool check = false;

    for(int i = sr; i < sr + size; i++){
        for(int j=sc; j < sc + size; j++) {
            if(Map[i][j] != prev) {
                cout << "(";
                int newSize = size /2;
                decompress(sr, sc, newSize);
                decompress(sr, sc + newSize, newSize);
                decompress(sr + newSize, sc, newSize);
                decompress(sr+ newSize, sc + newSize, newSize);
                cout << ")";
                check = true;
                break;
            }
        }
        if(check)   break;
    }
    if(!check)   cout << prev;

}

int main()
{
    input();
    decompress(0, 0, N);
}