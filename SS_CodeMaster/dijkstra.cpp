#include <iostream>

using namespace std;
const long long int max_num = 1000;
const long long int INF = 0xfffe;

int N;
int map[max_num][max_num];
int ans = 0;

void input()
{
    cin >> N;
    for(int i = 0; i <=N; i++) {
        for(int j = 0; j<=N; j++) {
            map[i][j] = INF;
        }
    }

    for(int i = 1; i<N; i++) {
        int r, c,v;
        cin >> r >> c >> v;
        map[r][c] = map[c][r] = v;
    }

    ans = 0;
}

void dijstra(int start)
{
    int min;
    int v = 0;
	int dp[max_num];
	int visited[max_num];


    for(int i = 1; i <=N; i++) {
        dp[i] = map[start][i];
        visited[i] = 0;
    }

	dp[start] = 0;

    for(int i = 1; i <=N ; i++) {
        min = INF;

        for(int j = 1; j<=N; j++) {
            if(visited[j] == 0 && min > dp[j]){
                min = dp[j]; 
                v = j;
            }
        }
        visited[v] = 1;

        for(int j = 1; j<=N; j++){
            if(dp[j] > dp[v] + map[v][j]) {
                dp[j] = dp[v] + map[v][j];
            }
        }
    }
}

void sol()
{
    for(int i = 1; i<= N; i++) {
        dijstra(i);
    }

    for(int i = 1; i<=N; i++) {
        for(int j = 1; j<=N; j++) {
            if(map[i][j] != INF){
                ans+= map[i][j];
            }
        }
    }
}

int main()
{
    int test_case;
    cin >> test_case;

    for(int i = 1; i <= test_case; i++) {
        input();
        sol();
        cout << "#" << i << " "  << ans;
    }

    return 0;
}