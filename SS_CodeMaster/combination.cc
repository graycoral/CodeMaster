#include<iostream>

using namespace std;

int N = 5;
int C = 3;
int arr[10];
int visited[10];

void combi(int idx, int s)
{
    if(idx >= C) {
        for(int i =0; i< C; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
        return;
    }

    for(int i = s; i<=N; i++) {
        if(visited[i] == 1) continue;
        arr[idx] = i;
        visited[i] = 1;
        combi(idx+1, i);
        arr[idx] = 0;
        visited[i] = 0;
    }
}


int main()
{
    cout <<"combination Test \n";
    combi(0, 1);
    return 0;
}