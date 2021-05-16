#include <stdio.h>

const int maxn = 115;

#define BLOCK_NUMBER 6
#define DIRECTION 4

int map[maxn][maxn];
int wormholePos[5][2];

int ans;
int T, N;

const int dy[] = {0,0,1,-1};
const int dx[] = {1,-1,0,0 };
const int changeDirection[BLOCK_NUMBER][DIRECTION] = {
	{0, 1, 2, 3},
	{1, 3, 0, 2},
	{1, 2, 3, 0},
	{2, 0, 3, 1},
	{3, 0, 1, 2},
	{1, 0, 1, 2},
};

void read() {
	scanf("%d", &N);
	for(int i = 1; i<=N; ++i) {
		for(int j=1; j<=N; ++j) {
			scanf("%d", &map[i][j]);
		}
	}
}

void setUptheWall()
{
	for(int i=0; i<=N; ++i) {
		map[i][0] = map[i][N+1] = map[0][i] = map[N+1][i] = 5;
	}
}

void wormhole(int &ny, int &nx, int wormhole_number)
{
	for(int i=1; i<=N ; ++i) {
		for(int j=1; j<=N; ++j) {
			if((ny != i || nx != j) && map[i][j] == wormhole_number) {
				ny= i; nx=j;
				return;
			}
		}
	}
}

void simulate(int sy, int sx, int d)
{
	int y=sy;
	int x=sx;

	int cnt = 0;

	while(1) {
		int ny = y + dy[d];
		int nx = x + dx[d];

		if((nx == sx && ny == sy) || map[ny][nx] == -1) {
			if(ans < cnt) ans = cnt;
			return;
		}

		if(map[ny][nx]) {
			if(map[ny][nx] < 6) {
				d = changeDirection[map[ny][nx]][d];
				cnt++;
			}
			else {
				wormhole(ny, nx, map[ny][nx]);
			}
		}

		x = nx;
		y=  ny;
	}
}

void sol()
{
	ans = 0;
	for(int i=1; i<=N; i++) {
		for(int j =1; j<=N; j++) {
			for(int d = 0; d<DIRECTION; d++	) {
				simulate(i, j, d);
			}
		}
	}
}

int main()
{
	//freopen("pin_ball_input_1.txt", "r", stdin);
	scanf("%d", &T);

	for (int test_case = 1; test_case <= T; ++test_case)
	{
		read();
		setUptheWall();
		sol();
		printf("#%d %d\n", test_case, ans);
	}

	return 0;
}

