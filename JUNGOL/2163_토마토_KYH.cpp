#include <iostream>
#include <algorithm>
#include <iomanip>
#include <queue>
#include <tuple>

#define MAXN	((int) 1000 + 10)
using namespace std;

queue <tuple<int, int, int>> q;
int Map[MAXN][MAXN];
int M, N;
int alive;

void input()
{
	cin >> M >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> Map[i][j];
			if (Map[i][j] == 1)	q.push(make_tuple(i, j, 0));
			else if (Map[i][j] == 0)	alive++;
		}
	}

}

int sol()
{
	int dr[] = { 1, -1, 0, 0 };
	int dc[] = { 0, 0, 1, -1 };

	while (!q.empty()) {
		auto cur = q.front(); q.pop();
		for (int i = 0; i < 4; i++) {
			int nr = get<0>(cur) + dr[i];
			int nc = get<1>(cur) + dc[i];
			int t = get<2>(cur);
			if (Map[nr][nc] != 0)	continue;
			if (nr > N || nc > M || nr <= 0 || nc <= 0)	continue;

			q.push(make_tuple(nr, nc, t + 1));
			Map[nr][nc] = t + 1;
			--alive;
			if (alive == 0)	return t + 1;
		}
	}



	return -1;
}

void PRT()
{
	cout << "===== print ===== " << endl;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cout << setw(3) << Map[i][j];
		}
		cout << endl;
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	input();
	//PRT();
	cout << sol();
	return 0;
}