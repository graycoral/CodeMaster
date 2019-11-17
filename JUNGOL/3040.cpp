#include <iostream>
#include <queue>
#include <algorithm>
#include <utility>

#define MAX 1001

using namespace std;

int map[MAX][MAX];
int day[MAX][MAX];
int N, M;
int dx[4] = {-1,1,0,0};
int dy[4] = {0,0,-1,1};

void init(){
    for(int i=1; i<=N; i++){
        for(int j=1; j<=M; j++){
            day[i][j] = 99999999;
        }
    }
}

int bfs(int x, int y){
    queue <pair<int,int>> q;
    q.push(make_pair(x,y));
    day[x][y] = 1;
    int ret = 99999999;

    while(!q.empty()){
        x = q.front().first;
        y = q.front().second;
        q.pop();
        //cout << x << ", " << y << endl;
        for(int i=0; i<4; i++){
            int nx = x + dx[i];
            int ny = y + dy[i];

            if(0<nx && nx<=N && 0<ny && ny<=M){
                if(map[nx][ny]!=-1 && day[nx][ny]>day[x][y]+1){
                    day[nx][ny] = day[x][y] + 1;
                    ret = min(ret, day[nx][ny]);
                    q.push(make_pair(nx,ny));
                }
            }
        }
    }
    return ret;
}

int main(void){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> M >> N;
    for(int i=1; i<=N; i++){
        for(int j=1; j<=M; j++){
            cin >> map[i][j];
        }
    }

    init();

    for(int i=1; i<=N; i++){
        for(int j=1; j<=M; j++){
            if(map[i][j] == 1)
                bfs(i,j);
        }
    }
     
    int ret = 0;

    for(int i=1; i<=N; i++){
        for(int j=1; j<=M; j++){
            if(day[i][j] > ret && day[i][j]!=99999999)
                ret = day[i][j];
            if(day[i][j] == 99999999 && map[i][j] == 0){
                cout << -1;
                return 0;
            }
               
        }
    }

    cout << ret-1;

    

    // for(int i=1; i<=N; i++){
    //     cout << endl;
    //     for(int j=1; j<=M; j++){
    //         cout << day[i][j] << " ";
    //     }
    // }

    return 0;
}