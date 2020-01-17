/**************************************************************
    Problem: 1335
    User: akachoochoo
    Language: C++
    Result: Success
    Time:2 ms
    Memory:2308 kb
****************************************************************/
 
 
// http://jungol.co.kr/bbs/board.php?bo_table=pbank&wr_id=614&sca=30
// Divide and Conquer
#include <iostream>
#include <queue>
#include <utility>
using namespace std;
 
#define MAX 128
 
int N;
int array[MAX+1][MAX+1];
int W, B;
 
void solve(int x, int y, int n){
     
    int curr_color = array[x][y];
 
    if(n == 1)
        if(curr_color == 1)
        {
            B++;
            return;
        }
        else
        {
            W++;
            return;
        }
    else
    {
         
        bool is_one_color = true;
 
        for(int nx=x; nx<x+n; nx++){
            for(int ny=y; ny<y+n; ny++){
                if(curr_color != array[nx][ny]){
                    is_one_color = false;
                    break;
                }
            }
        }
 
        if(is_one_color == true){
            if(curr_color == 1) B++;
            else W++;
            return;
        }
        else
        {
            solve(x,y,n/2);
            solve(x+n/2,y,n/2);
            solve(x,y+n/2,n/2);
            solve(x+n/2,y+n/2,n/2);
        }
         
    }
}
 
int main(void){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
 
    cin >> N;
 
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            cin >> array[i][j];
        }
    }
     
    solve(1,1,N);
 
    cout << W << '\n' << B;
 
    return 0;
}