#include <iostream>
#include <algorithm>
#include <map>
#include <queue>

using namespace std;
#define MAXN	((int)100+10)

int R, C;
int sr, sc;
int maxSec;
char Map[MAXN][MAXN];
int Data[MAXN][MAXN];
int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };

queue < pair<int, int>> q;

void input()
{
	cin >> C >> R;
	for (int i = 0; i < R; i++) {
		cin >> Map[i];
	}
	cin >> sc >> sr;
}

void PRT()
{
#if 1
	cout << "===========================" << endl;
	for (int i = 0; i <= R; i++) {
		cout << Map[i] << endl;
	}
#endif
	cout << "===========================" << endl;
	for (int i = 0; i <= R; i++) {
		for (int j = 0; j <= C; j++) {
			cout << Data[i][j] << " ";
		}
		cout << endl;
	}
	cout << "===========================" << endl;
}

void DFS(int r, int c, int sec)
{
	if (r <= 0 || c <= 0 || r > R || c > R) {
		return;
	}

	Data[r][c] = sec;
	PRT();
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			for (int k = 0; k < 4; k++) {
				int nr = r + dr[k]; int nc = c + dc[k];
				if (Map[nr][nc] == 0 || Map[nr][nc] == '0' || (Data[nr][nc] > 0))	continue;
				DFS(nr, nc, sec + 1);
			}
		}
	}
}

void BFS()
{
	q.push({ sr - 1,sc - 1 });
	Data[sr - 1][sc - 1] = 3;

	while (!q.empty())
	{
		int curR = q.front().first;
		int curC = q.front().second;
		q.pop();
		for (int i = 0; i < 4; i++) {
			int nr = curR + dr[i];
			int nc = curC + dc[i];
			if (nr < 0 || nc < 0 || nr >= R || nc >= C)	continue;
			if (Map[nr][nc] == 0 || Map[nr][nc] == '0' || (Data[nr][nc] > 0))	continue;
			Data[nr][nc] = Data[curR][curC] + 1;
			q.push({ nr, nc });
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	int nodie = 0;
	input();
	BFS();
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (Map[i][j] == '1' && Data[i][j] == 0)	nodie++;
			if (maxSec < Data[i][j]) maxSec = Data[i][j];
		}
	}
	//PRT();
	cout << maxSec << endl;
	cout << nodie;
	return 0;
}