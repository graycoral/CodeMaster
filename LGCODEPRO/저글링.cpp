#include <iostream>
#include <algorithm>
#include <queue>

#define MAX 101

using namespace std;

int N, M, X, Y;
int map[MAX][MAX];
int attacked[MAX][MAX];
int deadtime[MAX][MAX];
int dx[4] = {-1,1,0,0};
int dy[4] = {0,0,-1,1};

int attack_BFS(int x, int y){
    queue<pair<int,int>> q;
    q.push(make_pair(x,y));
    attacked[y][x] = 1;
    deadtime[y][x] = 3;

    int ret = 3;

    while(!q.empty()){

        x = q.front().first;
        y = q.front().second;
        q.pop();
    
        for(int i=0; i<4; i++){
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(0<nx && nx<=N && 0<ny && ny<=M){
                if(attacked[ny][nx] == 0 && map[ny][nx] == 1){
                    attacked[ny][nx] = 1;
                    deadtime[ny][nx] = deadtime[y][x]+1;
                    q.push(make_pair(nx,ny));
                    ret = max(ret, deadtime[ny][nx]);

                    //cout << nx << ", " << ny << ", "<< deadtime[ny][nx] <<endl;
                }
            }
        }
    }
    return ret;
}

int main(void){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;

    for(int i=1; i<=M; i++){
        for(int j=1; j<=N; j++){
            scanf("%1d",&map[i][j]);
        }
    }

    cin >> X >> Y;
    cout << attack_BFS(X,Y) << endl;

    int total = 0;
    for(int i=1; i<=M; i++){
        for(int j=1; j<=N; j++){
            if(map[i][j] == 1 && attacked[i][j] == 0)
            { 
                //cout << i << j;
                total++;
            }
        }
    }

    cout << total;


    return 0;
}