// 장기
#include <iostream>
#include <queue>
#include <utility>
#define MAX 101

using namespace std;

int N, M, R, C, S, K;
int map[MAX][MAX];
int try_cnt;
int r_off[8] = {-1, -2, -2, -1, 1, 2, 2, 1};
int c_off[8] = {-2, -1, 1, 2, 2, 1, -1, -2};

int bfs(int r, int c){
    queue <pair<int, int>> q;
    q.push(make_pair(r,c));
    map[r][c] = 0;

    while(!q.empty()){
        r = q.front().first;
        c = q.front().second;
        q.pop();
        
        for(int i=0; i<8; i++){
            int nr = r + r_off[i];
            int nc = c + c_off[i];

            if(0<nr && nr<=N && 0<nc && nc<=M){
                if(map[nr][nc] > map[r][c]+1){
                    q.push(make_pair(nr,nc));
                    map[nr][nc] = map[r][c] + 1;
                }
            }
        }
    }

    return map[S][K];
}

int main(void){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    cin >> R >> C >> S >> K;

    for(int i=1; i<=N; i++){
        for(int j=1; j<=M; j++){
            map[i][j] = 1000000000;
        }
    }

    cout << bfs(R, C);
    
    return 0;
}