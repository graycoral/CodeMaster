#include <iostream>

using namespace std;

enum class STATE {
	DEAD = -1,
	NOT_VISITED = 0,
	INACTIVE,
	ACTIVE
};

const int maxn = 50 + 2;
int N, M, K;
int map[maxn][maxn];
int countMap[maxn][maxn];
STATE stateMap[maxn][maxn]; // -1 : dead , 0 : not visitied , 1 : inactive, 2: active 
int alive;

int dr[] = { 1, -1, 0 , 0 };
int dc[] = { 0 , 0 , 1, -1 };

void show(int k)
{
	cout << "=============" << k << "=============" << endl;
	for (int i = 0; i < N+K; i++) {
		for (int j = 0; j < M+K; j++) {
			cout << map[i][j] << "  ";
		}
		cout << endl;
	}
	cout << "=============" << k << "=============" << endl << endl;
}


void input()
{
	for (int i = 0; i < maxn; i++) {
		for (int j = 0; j < maxn; j++) {
			map[i][j] = 0;
		}
	}

	cin >> N >> M >> K;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			countMap[i][j] = map[i][j];
			stateMap[i][j] = STATE::INACTIVE;
		}
	}
}

void move(int r, int c, int v)
{
	if (stateMap[r][c] == STATE::DEAD)	return;

	if(stateMap[r][c] == STATE::INACTIVE) {
		countMap[r][c]--;
		if(countMap[r][c] == 0) {
			stateMap[r][c] = STATE::ACTIVE;
			countMap[r][c] = map[r][c];
		}
	}
	else if (stateMap[r][c] == STATE::ACTIVE) {
		countMap[r][c]--;
		if (countMap[r][c] == 0) {
			stateMap[r][c] = STATE::DEAD;
			map[r][c] = 0;
			for (int i = 0; i < 4; i++) {
				int nr = r + dr[i]; int nc = c + dc[i];
				if (nr >= maxn || nc >= maxn || nr < 0 || nc < 0)	continue;
				if (stateMap[nr][nc] == STATE::DEAD)	continue;
				if (map[nr][nc] > v || (stateMap[nr][nc] != STATE::INACTIVE || stateMap[nr][nc] != STATE::NOT_VISITED)) continue;
				map[nr][nc] = v;
				stateMap[nr][nc] = STATE::INACTIVE;
				// TBD if change map value???
				countMap[nr][nc] = map[nr][nc];
			}
		}
	}
	else { // stateMap[r][c] == STATE::NOT_VISITED
		map[r][c] = countMap[r][c] = v;
		stateMap[r][c] = STATE::INACTIVE;
	}
}

void sol()
{
	for (int i = 0; i < K; i++) {
		show(i);
		for (int r = 0; r < N; r++) {
			for (int c = 0; c < M; c++) {
				if (stateMap[r][c] == STATE::DEAD || map[r][c] == 0)	continue;
				move(r, c, map[r][c]);
			}
		}
	}
}

int count()
{
	alive = 0;
	for (int i = 0; i < N + K; i++) {
		for (int j = 0; j < M + K; j++) {
			if (stateMap[i][j] > STATE::INACTIVE) ++alive;
		}
	}

	return alive;
}

int main()
{
	int test_case;
	freopen("5654_줄기세포배양.txt", "r", stdin);

	cin >> test_case;
	for (int i = 0; i < test_case; i++) {
		input();
		sol();
		cout << "#" << i + 1 << " " << count() << endl;
	}

	return 0;
}