#include <iostream>

using namespace std;

#define MIN(a, b) (a > b ? b: a)
const int max_num = 50 + 1;
const int INF = 987654321;

const int direction[7][4] =
{
	{0, 0, 0, 0},
	{0, 0, 1, 1},
	{1, 1, 0, 0},
	{1, 0, 1, 0},
	{1, 0, 0, 1},
	{0, 1, 0, 1},
	{0, 1, 1, 0}
};

const int changedirection[7][4] = 
{
	{0, 0, 0, 0},
	{2, 2, 1, 1},
	{2, 2, 1, 1},
	{4, 0, 0, 6},
	{3, 0, 5, 0},
	{0, 6, 0, 4},
	{0, 5, 3, 0}
};


const int changeNewdirection[7][4] =
{
	{0, 0, 0, 0},
	{2, 2, 1, 1},
	{2, 2, 1, 1},
	{3, 6, 3, 4},
	{5, 4, 4, 3},
	{4, 5, 5, 6},
	{3, 6, 5, 6}
};

int map[max_num][max_num];
int visited[max_num][max_num];
int dp[max_num][max_num][4];
int N, ans = 987654321;

const int dr[] = { -1, 1, 0, 0 };
const int dc[] = { 0, 0, -1, 1 };

void input()
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			map[i][j] = 0;
		}
	}

	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			visited[i][j] = INF;
			cin >> map[i][j];
			for (int d = 0; d < 4; d++) {
				dp[i][j][d] = 0;
			}
		}
	}

	ans = INF;
}

bool invaildRang(int r, int c)
{
	return (r < 0 || c < 0 || r >= N || c >= N) ? 1 : 0;
}

bool checkVaild(int r, int c, int cnt)
{
	if (invaildRang(r, c))	return false;
	if (map[r][c] == 0)		return false;
	if (visited[r][c] <= cnt && visited[r][c] != INF)		return false;

	return true;
}

void DFS(int r, int c, int dir, int cnt)
{
	if (visited[r][c] <= cnt && visited[r][c] != INF)	return;
	if (cnt > ans)	return;
	if ((r == N - 1) && (c == N - 1)) {
		ans = MIN(ans, cnt);
		return;
	}
	else {
		visited[r][c] = cnt;

		for (int d = 0; d < 4; d++) {
			int nr = r + dr[d];
			int nc = c + dc[d];
			if (!checkVaild(nr, nc, cnt+1)) continue;

			// original
			if (direction[map[nr][nc]][d] == 1) {
				DFS(nr, nc, d, cnt + 1);
			}
			// next node change
			else {
				int changedBlock = changeNewdirection[map[nr][nc]][d];
				if (direction[changedBlock][d] == 1) {
					int curBlock = map[nr][nc];
					map[nr][nc] = changedBlock;
					DFS(nr, nc, d, cnt + 1);
					map[nr][nc] = curBlock;
				}
			}
			
			// original node change
			int changedBlock = changedirection[map[r][c]][d];
			if (direction[changedBlock][d] == 1) {
				int curBlock = map[nr][nc];
				map[nr][nc] = changedBlock;
				DFS(nr, nc, d, cnt + 1);
				map[nr][nc] = curBlock;
			}
		}
	}
}

int main()
{
	int test_case = 1;
	freopen("swea_4340_input.txt", "r", stdin);
	cin >> test_case;

	for (int i = 1; i <= test_case; i++) {
		input();
		DFS(0, 0, 3, 1);
		cout << "#" << i << " " << ans << endl;
	}
	return 0;
}