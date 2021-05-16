#include<iostream>
#include<iomanip>

using namespace std;

#define MAX(a,b)	( a>b ? a : b)
const int maxN = 110 + 1;
const int BLACKHOLE = -1;

typedef struct Pos {
	int r, c;
} Pos ;

typedef struct WH {
	Pos pos;
	int v;
} WH;

WH wh[maxN];
int whSize = 0;

int Map[maxN][maxN];
int N;
int ans; 
int startPos_R;
int startPos_C;
bool startFlag = false;

int dr[] = {-1, 1, 0, 0};
int dc[] = { 0, 0, -1, 1};

int dic[6][4] = {
		{0, 0, 0, 0},
		{1, 3, 0, 2},
		{3, 0, 1, 2},
		{2, 0, 3, 1},
		{1, 2, 3, 0},
		{1, 0, 3, 2}
};

void show()
{
	for (int i = 0; i <= N + 1; i++) {
		for (int j = 0; j <= N + 1; j++) {
			cout << setw(3) << Map[i][j];
		}
		cout << endl;
	}
}

void input()
{
	for (int i = 0; i <= N + 1; i++) {
		for (int j = 0; j <= N + 1; j++) {
			Map[i][j] = 0;
		}
	}

	for (int i = 0; i < whSize; i++) {
		wh[i].pos.r = wh[i].pos.c = wh[i].v = 0;
	}
	ans = whSize = startPos_R = startPos_C = 0;
	startFlag = false;
	cin >> N;

	for (int i = 0; i <= N + 1; i++) {
		for (int j = 0; j <= N + 1; j++) {
			if (i == 0 || j == 0 || i == N +1 || j == N +1) {
				Map[i][j] = 5;
			}
			else {
				cin >> Map[i][j];
				if (Map[i][j] >= 6 && Map[i][j] <= 10) {
					wh[whSize].pos.r = i;
					wh[whSize].pos.c = j;
					wh[whSize++].v = Map[i][j];
				}
			}
		}
	}
}

int invalidRange(int r, int c)
{
	if (r < 0 || c < 0 || r > N || c > N)	return 1;
	return 0;
}

Pos searchWH(int r, int c, int v)
{
	Pos retPos;
	retPos.r = -1; 	retPos.c = -1;

	for (int i = 0; i < whSize; i++) {
		if (v == wh[i].v && (wh[i].pos.r != r || wh[i].pos.c != c)) {
			retPos.r = wh[i].pos.r;
			retPos.c = wh[i].pos.c;
			break;
		}
	}

	return retPos;
}

int count(int r, int c, int d)
{
	int Score = 0;
	
	while (1)
	{
		int nr = r + dr[d]; int nc = c + dc[d];
		if (invalidRange(nr, nc)) return Score;
		if (Map[nr][nc] == BLACKHOLE || (nr == startPos_R && nc == startPos_C)) return Score;
		else {
			// Check Warmhole
			if (Map[nr][nc] >= 6 && Map[nr][nc] <= 10) {
				Pos sWh = searchWH(nr, nc, Map[nr][nc]);
				nr = sWh.r; nc = sWh.c;
			}
			else if (Map[nr][nc] >= 1 && Map[nr][nc] <= 5) {
				// check Block
				Score++;
				d = dic[Map[nr][nc]][d];
			}
		}
		r = nr;
		c = nc;
	}
	return Score;
}

void sol()
{
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			if (Map[r][c] == 0) {
				startPos_R = r; startPos_C = c;
				
				for (int d = 0; d < 4; d++) {
					int tmpCnt = count(r, c, d);
					ans = MAX(ans, tmpCnt);
				}
			}
		}
	}
}


int main(int argc, char** argv)
{
	int test_case;
	int T;

	freopen("pin_ball_input_1.txt", "r", stdin);
	cin >> T;
	
	for (test_case = 1; test_case <= T; ++test_case)
	{
		input();
		sol();
		cout << "#" << test_case << " " << ans << endl;
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}