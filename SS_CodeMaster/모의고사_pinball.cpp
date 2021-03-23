#include <iostream>
#include <cstring>

#define MAX(a, b)  ((a) > (b)) ? (a) : (b)
using namespace std;
constexpr int MAXN = 100 + 10;

int map[MAXN][MAXN];
int N;
struct pos {
	int r, c;
};

struct pos wh[10][2];
int ansCnt = 0;
const int dr[] = { 1, -1, 0, 0 };
const int dc[] = { 0, 0, 1, -1 };

const int changeDirection[4][6] = {
	{0,2,1,1,3,1},
	{0,0,2,3,0,0},
	{0,3,3,0,1,3},
	{0,1,0,2,2,2}
};

void input()
{
	int whCnt = 0;
	int bhIdx = 0;
	ansCnt = 0;
	cin >> N;

	memset(map, 0, sizeof(map));
	memset(wh, 0, sizeof(wh));

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
			if (map[i][j] >= 6) {
				if (wh[map[i][j]][0].r == 0) {
					wh[map[i][j]][0].r = i;
					wh[map[i][j]][0].c = j;
				}
				else {
					wh[map[i][j]][1].r = i;
					wh[map[i][j]][1].c = j;
				}
			}
		}
	}

	for (int i = 0; i <= N; i++) {
		map[0][i] = 5;
		map[i][0] = 5;
		map[N + 1][i] = 5;
		map[i][N + 1] = 5;
	}
}

void move(int r, int c, int d)
{
	int ans = 0;
	int dic = d;
	int startR = r;
	int startC = c;

	int curR = r;
	int curC = c;

	//cout << "Start : " << startR << "," << start.c << "," << dic;
	while (1) {
		curR= curR+ dr[dic];
		curC = curC + dc[dic];

		if ((curR== startR && curC == startC) || (map[curR][curC] == -1)) {
			ansCnt = MAX(ansCnt, ans);
			//cout << " : " << ans << endl;
			break;
		}

		if (map[curR][curC]) {
			// Warmhole Check and change current position
			if (map[curR][curC] >= 6 && map[curR][curC] <= 10) {
				int whR = curR;
				int whC = curC;
				if (wh[map[whR][whC]][0].r == curR&& wh[map[whR][whC]][0].c == curC) {
					curR= wh[map[whR][whC]][1].r;
					curC = wh[map[whR][whC]][1].c;
				}
				else {
					curR= wh[map[whR][whC]][0].r;
					curC = wh[map[whR][whC]][0].c ;
				}
			}
			// block 
			else if (map[curR][curC] <= 5) {
				ans++;
				dic = changeDirection[dic][map[curR][curC]];
			}
		}
	}
}

void sol(int test_case)
{
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (map[i][j] != 0) continue;
			for (int d = 0; d < 4; d++) {
				move(i, j, d);
			}
		}
	}

	std::cout << "#" << test_case << " " << ansCnt << endl;
}

int main()
{
	ios_base::sync_with_stdio(false);
	std::cin.tie(0); std::cout.tie(0);

	int test_case;
	int T;

	//freopen("pin_ball_input_1.txt", "r", stdin);
	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		input();
		sol(test_case);
	}
	return 0;
}