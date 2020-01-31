// http://www.jungol.co.kr/bbs/board.php?bo_table=pbank&wr_id=1360&sca=99&sfl=wr_subject&stx=%EC%A7%80%ED%95%98%EC%B2%A0
// 2097 : 지하철, Shortest Path, 

// Floyd-Warhall [O(V^3)] --> special judge fail
// Dijkstra [O(V^2+E) or O(|E|lg|v|)] --> all pass
// Bellman-Ford [O(|V|*|E|)] 
// SPFA(Shortest Path Fast Algorithm) [O(|E|)] or [O(|E|*|V|)]

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_N 101

int N, M;
int W[MAX_N][MAX_N];
int S = 1;

void solve_Floyd(){
    int path[MAX_N][MAX_N];

    for(int k=1; k<=N; k++){
        for(int i=1; i<=N; i++){
            for(int j=1; j<=N; j++){
                if(W[i][j] > W[i][k] + W[k][j]){
                    // cout << W[i][j] << " : " << W[i][k] + W[k][j] << endl;
                    W[i][j] = W[i][k] + W[k][j];
                    path[i][j] = k;
                }
            }
        }
    }

    // for(int i=1; i<=N; i++){
    //     for(int j=1; j<=N; j++){
    //         cout << W[i][j] << "(" << path[i][j] << ") ";
    //     }
    //     cout 
    //     << endl;
    // } 

    cout << W[1][M] << endl;
    

    int temp = M;
    cout << S << " ";
    while(path[S][temp] > 0){
        cout << path[S][temp] << " ";
        temp = path[S][temp];
    }
    cout << M;
}

void solve_Dijkstra(){
    int dist[MAX_N];
    int path[MAX_N];
    int visit[MAX_N];

    // Initialize dist
    for(int i=1; i<=N; i++){
        dist[i] = INT16_MAX;
        visit[i] = 0;
        path[i] = 0;
    }
    dist[1] = 0;

    for(int i=1; i<=N; i++){
        int minNode, minVal = INT16_MAX;
        for(int j=1; j<=N; j++){
            if(visit[j]==0 && minVal>dist[j])
            {
                minNode = j;
                minVal = dist[j];
            }
        }
        printf("i:[%d], minNode:[%d], minVal:[%d], dist:[", i, minNode, minVal);
        for(int k=1; k<=N; k++)
            printf("%d,",dist[k]);
        printf("], path:[");    
        for(int k=1; k<=N; k++)
            printf("%d,",path[k]);
        printf("]\n");    

        visit[minNode] = 1;
        for(int j=1; j<=N; j++){
            if(dist[j] > minVal + W[minNode][j]){
                dist[j] = minVal + W[minNode][j];
                path[j] = minNode;
            }
        }

    }

    cout << dist[M] << endl;

    vector<int> ans;
    int temp = M;
    ans.push_back(M);
    while(1){
        ans.push_back(path[temp]);
        temp = path[temp];
        if(temp == S) break;
    }
    reverse(ans.begin(), ans.end());
    for(auto v : ans)
        cout << v << " ";

}

void solve_BF(){
    int i;
}

void solve_SPFA(){
    int i;
}

int main(void){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;
    
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            cin >> W[i][j];
        }
    }

    solve_Dijkstra();

    

    return 0;
}