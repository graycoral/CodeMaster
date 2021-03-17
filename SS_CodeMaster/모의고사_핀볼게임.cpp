#include <iostream>

#define MAX(a, b)  ((a) > (b)) ? (a) : (b)
using namespace std;
constexpr int MAXN = 100 + 10;

int map[MAXN][MAXN];
int N;
struct pos {
	int r, c;
};

struct pos wh[MAXN][2];
struct pos bh;
int ansCnt = 0;

void input()
{
	int whCnt = 0;
	cin >> N;
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
			if (map[i][j] == -1) {
				bh.r = i;
				bh.c = j;
			}
		}
	}
}

void sol(int test_case)
{
	int ans = 0;
	int dr[] = { 1, -1, 0, 0 };
	int dc[] = { 0, 0, 1, -1};

	struct pos start;
	struct pos cur = {1,1};
	
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (map[i][j] != 0) continue;

			for (int d = 0; d < 4; d++) {
				int dic = d;				
				int startFlag = 0;
				start.r = i;
				start.c = j;
				cur = start;

				while (1) {
					if (startFlag == 1 && cur.r == start.r && cur.c == start.c)	break;
					if (cur.r == bh.r && cur.c == bh.c)	break;

					if (cur.r < 1)		{ cur.r = 2; dic = 1; }
					else if (cur.r > N) { cur.r = N-1; dic = 0; }
					else if (cur.c < 1) { cur.c = 2; dic = 2; }
					else if (cur.c > N) { cur.c = N-1; dic = 3; }
					
					// change start Flag
					startFlag = 1;

					// Warmhole Check and change current position
					if (map[cur.r][cur.c] >= 6 && map[cur.r][cur.c] <= 10) {
						if (wh[map[cur.r][cur.c]][0].r == cur.r) {
							cur.r = wh[map[cur.r][cur.c]][1].r;
							cur.c = wh[map[cur.r][cur.c]][1].c;
						}
						else {
							cur.r = wh[map[cur.r][cur.c]][0].r;
							cur.c = wh[map[cur.r][cur.c]][0].c;
						}
					}
					// block 
					else if (map[cur.r][cur.c] >= 1 && map[cur.r][cur.c] <= 4) {
						ans += map[cur.r][cur.c];

						int nr = cur.r + dr[dic];
						int nc = cur.c + dc[dic];


						if (nr > cur.r) {
							if ((map[nr][nc] == 2) || (map[nr][nc] == 3) || (map[nr][nc] == 5)) {
								nr -= 2;
								dic = 0;
							}
							else if ((map[nr][nc] == 1)) {
								nc += 1;
								dic = 2;

							}
							else if ((map[nr][nc] == 4)) {
								nc -= 1;
								dic = 3;
							}
						}
						else if (nc > cur.c) {
							if ((map[nr][nc] == 1) || (map[nr][nc] == 2) || (map[nr][nc] == 5)) {
								nc -= 2;
								dic = 3;
							}
							else if ((map[nr][nc] == 3)) {
								nr += 1;
								dic = 1;
							}
							else if ((map[nr][nc] == 4)) {
								nr -= 1;
								dic = 0;
							}
						}
						else if (nr < cur.r) {
							if ((map[nr][nc] == 1) || (map[nr][nc] == 4) || (map[nr][nc] == 5)) {
								nr += 2;
								dic = 1;
							}
							else if ((map[nr][nc] == 2)) {
								nc += 1;
								dic = 2;
							}
							else if ((map[nr][nc] == 3)) {
								nc -= 1;
								dic = 3;
							}
						}
						else if (nc < cur.c) {
							if ((map[nr][nc] == 3) || (map[nr][nc] == 4) || (map[nr][nc] == 5)) {
								nc += 2;
								dic = 2;
							}
							else if ((map[nr][nc] == 1)) {
								nr -= 1;
								dic = 0;
							}
							else if ((map[nr][nc] == 2)) {
								nr += 1;
								dic = 1;
							}
						}
						
						cur.r = nr;
						cur.c = nc;
					}
					else {
						cur.r += dr[dic];
						cur.c += dc[dic];
					}
				}
				ansCnt = MAX(ansCnt, ans);
			}
			
		}
	}	

	cout << "#" << test_case << " " << ansCnt;
}

int main()
{
	ios_base::sync_with_stdio(false);
	std::cin.tie(0); std::cout.tie(0);

	int test_case;
	int T;

	freopen("모의고사_핀볼게임_input.txt", "r", stdin);
	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		input();
		sol(test_case);
	}
	return 0;
}