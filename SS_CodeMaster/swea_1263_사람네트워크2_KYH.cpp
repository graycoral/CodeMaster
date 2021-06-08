#include <iostream>

using namespace std;

const long long int INF = 987654321;
const int mam_num = 1000 + 1;

#define MIN(a,b) ( a> b ? b:a)

int map[mam_num][mam_num];
int N;
int dp[mam_num];
int visited[mam_num];
int min_num = 987654321;

void input()
{
	min_num = 987654321;
	cin >> N;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 0) map[i][j] = INF;
			if (i == j) map[i][j] = 0;
		}
	}
}

void dijkstra(int start)
{
	int dist[mam_num];
	int v = 0;
	for (int i = 1; i <= N; i++) {
		dist[i] = map[start][i];
		visited[i] = 0;
	}

	dist[start] = 0;

	for (int i = 1; i <= N; i++) {
		min_num = INF;

		for (int j = 1; j <= N; j++) {
			if (visited[j] == 0 && min_num > dist[j]) {
				min_num = dist[j];
				v = j;
			}
        }

		visited[v] = 1;

		for (int j = 1; j <= N; j++) {
			if (dist[j] > dist[v] + map[v][j]) {
				dist[j] = dist[v] + map[v][j];
			}
		}
    }
}

void floydwashall()
{
	for (int k = 0; k < N; k++) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (i == j) continue;
				map[i][j] = MIN(map[i][j], map[i][k] + map[k][j]);
			}
		}
	}
}

int main()
{
    int test_case;
    freopen("swea_1263_input.txt", "r", stdin);
	cin >> test_case;
    for(int i = 1; i<=test_case; i++) {
        input();
		floydwashall();

		for (int i = 0; i < N; i++) {
			int tmp = 0;
			for (int j = 0; j < N; j++) {
				if (i == j) continue;
				tmp += map[i][j];
			}
			min_num = MIN(min_num, tmp);
		}
		cout << "#" << i << " " << min_num << endl;
    }
    return 0;
}

