#include <iostream>
#include <iomanip>

using namespace std;

#define SWAP(a, b) {int t = a; a=b; b=t;}

const int maxn = 20 + 1;
const int emptyNum = 8;
const int redBombNum = 9;

int map[maxn][maxn];
int numArr[maxn];
int v[maxn][maxn];
int N = 1, M = 0;
int ans;
int maxbombCnt = 0xfffe;
int bombCnt = 0;

int tmpMaxPosR = 0;
int tmpMaxPosC = 0;

int maxPosR = 0;
int maxPosC = 0;

int dr[] = { 1, -1, 0, 0 };
int dc[] = { 0, 0, 1, -1 };

typedef struct pos {
	int r;
	int c;
} Pos;

int startPosR = 0;
int startPosC = 0;

void input()
{
	ans = 0;
	tmpMaxPosR = tmpMaxPosC = 0;
	maxPosR = maxPosC = 0;
	maxbombCnt = 0xfffe;
	for (int i = 0; i < maxn; i++) {
		for (int j = 0; j < maxn; j++) {
			map[i][j] = v[i][j] = 0;
		}
		numArr[i] = 0;
	}

	cin >> N >> M;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			cin >> map[r][c];
			if (map[r][c] == 0)	map[r][c] = redBombNum;
			numArr[map[r][c]]++;
		}
	}

}

#define DEBUG (0)

void show(string str)
{
#if DEBUG	
	cout << "=============" << str << " : "<< ans << "=======================" << endl;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			if (map[r][c] == 9) {
				cout << setw(3) << 0;
			}
			else if (map[r][c] == 8) {
				cout << setw(3) << -2;
			}
			else {
				cout << setw(3) << map[r][c];
			}
			
		}
		cout << endl;
	}
	cout << "==========================================================" << endl;
#endif
}

int move(int r, int c, int value)
{
	int retValue = 1;
	if (r >= N || c >= N || r < 0 || c < 0)	return 0;
	if (v[r][c] == 1)	return 0;

	v[r][c] = 1;
	
	if (map[r][c] == redBombNum) bombCnt++;
	else {
		if (r > tmpMaxPosR) {
			tmpMaxPosR = r;
			tmpMaxPosC = c;
		} 
		else if (r == tmpMaxPosR) {
			if (c < tmpMaxPosC)	tmpMaxPosC = c;
		}
	}
	for (int i = 0; i < 4; i++) {
		int nr = r + dr[i]; int nc = c + dc[i];
		if (nr >= N || nc >= N || nr < 0 || nc < 0)	continue;
		if (v[nr][nc] == 1)	continue;
		if (map[nr][nc] == value || map[nr][nc] == redBombNum) {
			retValue += move(nr, nc, value);
		}
	}

	return retValue;
}

int count()
{
	show("FindBestBundle");
	int maxCnt = 0;	
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			tmpMaxPosR = tmpMaxPosC = 0; bombCnt = 0;

			if (v[r][c] == 1 || map[r][c] <= 0 || map[r][c] == emptyNum)	continue;
			int cnt = 0;
			cnt = move(r, c, map[r][c]);
			
			if (cnt > maxCnt) {
				maxCnt = cnt;
				startPosR = r; startPosC = c;
				maxbombCnt = bombCnt;
				maxPosR = tmpMaxPosR;
				maxPosC = tmpMaxPosC;
				maxbombCnt = bombCnt;
			}
			else if (cnt == maxCnt) {
				if (maxbombCnt > bombCnt) {
					startPosR = r; startPosC = c;
					maxbombCnt = bombCnt;
					maxPosR = tmpMaxPosR;
					maxPosC = tmpMaxPosC;
					maxbombCnt = bombCnt;
				}
				else if (maxbombCnt == bombCnt) {
					if (tmpMaxPosR > maxPosR) {
						startPosR = r; startPosC = c;
						maxbombCnt = bombCnt;
						maxPosR = tmpMaxPosR;
						maxPosC = tmpMaxPosC;
						maxbombCnt = bombCnt;
					}
					else if (tmpMaxPosR == maxPosR) {
						if (tmpMaxPosC < maxPosC) {
							startPosR = r; startPosC = c;
							maxbombCnt = bombCnt;
							maxPosR = tmpMaxPosR;
							maxPosC = tmpMaxPosC;
							maxbombCnt = bombCnt;
						}
					}
				}
			}

			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					v[i][j] = 0;
				}
			}
		}
	}
	if (maxCnt == 1)	return 0;
	//if (numArr[map[startPosR][startPosC]] != (maxCnt - maxbombCnt)) return 0;
	return maxCnt;
}

void remove(int r, int c, int value)
{
	if (r >= N || c >= N || r < 0 || c < 0)	return;
	map[r][c] = emptyNum;
	//v[r][c] = 0;
	for (int i = 0; i < 4; i++) {
		int nr = r + dr[i]; int nc = c + dc[i];
		if (nr >= N || nc >= N || nr < 0 || nc < 0)	continue;
		if (value == map[nr][nc] || map[nr][nc] == redBombNum) {
			remove(nr, nc, value);
		}
	}
}

void gravity()
{
	for (int c = 0; c < N; c++) {
		int idx = 0;
		int tmpArr[100] = { 0, };
		for (int r = N - 1; r >= 0; r--) {
			if (map[r][c] == emptyNum)	continue;
			if (map[r][c] == -1)	idx = N - 1 - r;
			tmpArr[idx++] = map[r][c];
		}
		for (int i = 0; i < N; i++) {
			if (tmpArr[i] == 0)	tmpArr[i] = emptyNum;
			map[N - 1 - i][c] = tmpArr[i];
		}
	}
	show("gravity");
}

void reorder()
{
	int tmpMap[maxn][maxn];

	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			tmpMap[N - 1 - c][r] = map[r][c];
		}
	}

	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			map[r][c] = tmpMap[r][c];
		}
	}
	show("reorder");
}

void sol()
{
	int removeCnt = count();
	while (removeCnt) {
		ans += (removeCnt * removeCnt);
		remove(startPosR, startPosC, map[startPosR][startPosC]);
		show("remove");
		gravity();
		reorder();
		gravity();
		removeCnt = count();
	}
}

int main()
{
	int test_case = 1;

	/*freopen("»ö±òÆøÅº.txt", "r", stdin);
	cin >> test_case;*/

	for (int i = 1; i <= test_case; i++) {
		input();
		sol();
		//cout << "#" << i << " " << ans <<endl;
		cout << ans << endl;
	}
	return 0;
}