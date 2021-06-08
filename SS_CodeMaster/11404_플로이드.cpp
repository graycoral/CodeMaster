#include <iostream>
#include <iomanip>

using namespace std;
#define MIN(a, b) (a > b ? b : a)
const int max_num = 100000 + 1;
const int INF = 987654321;

int map[110][110];
int N, E;


void input()
{
	cin >> N >> E;

	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			map[r][c] = INF;
		}
	}

	for (int i = 0; i < E; i++) {
		int tmpR, tmpC, value;
		cin >> tmpR >> tmpC >> value;
		if (map[tmpR][tmpC] > value) {
			map[tmpR][tmpC] = value;
		}
	}
}

int main()
{
	input();

	for (int k = 1; k <= N; k++) {
		for (int r = 1; r <= N; r++) {
			for (int c = 1; c <= N; c++) {
				if (r == c)	continue;
				if (map[r][k] == INF || map[k][c] == INF)	continue;
				map[r][c] = MIN(map[r][c], map[r][k] + map[k][c]);
			}
		}
	}

	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			if (r == c || map[r][c] == INF)
				cout << 0 << " ";
			else
				cout << map[r][c] << " ";
		}
		cout << endl;
	}
}