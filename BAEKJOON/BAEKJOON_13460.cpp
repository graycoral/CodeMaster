#include <iostream>

/*
https://www.acmicpc.net/problem/13460
문제
스타트링크에서 판매하는 어린이용 장난감 중에서 가장 인기가 많은 제품은 구슬 탈출이다. 구슬 탈출은 직사각형 보드에 빨간 구슬과 파란 구슬을 하나씩 넣은 다음, 빨간 구슬을 구멍을 통해 빼내는 게임이다.

보드의 세로 크기는 N, 가로 크기는 M이고, 편의상 1×1크기의 칸으로 나누어져 있다. 가장 바깥 행과 열은 모두 막혀져 있고, 보드에는 구멍이 하나 있다. 빨간 구슬과 파란 구슬의 크기는 보드에서 1×1크기의 칸을 가득 채우는 사이즈이고, 각각 하나씩 들어가 있다. 게임의 목표는 빨간 구슬을 구멍을 통해서 빼내는 것이다. 이때, 파란 구슬이 구멍에 들어가면 안 된다.

이때, 구슬을 손으로 건드릴 수는 없고, 중력을 이용해서 이리 저리 굴려야 한다. 왼쪽으로 기울이기, 오른쪽으로 기울이기, 위쪽으로 기울이기, 아래쪽으로 기울이기와 같은 네 가지 동작이 가능하다.

각각의 동작에서 공은 동시에 움직인다. 빨간 구슬이 구멍에 빠지면 성공이지만, 파란 구슬이 구멍에 빠지면 실패이다. 빨간 구슬과 파란 구슬이 동시에 구멍에 빠져도 실패이다. 빨간 구슬과 파란 구슬은 동시에 같은 칸에 있을 수 없다. 또, 빨간 구슬과 파란 구슬의 크기는 한 칸을 모두 차지한다. 기울이는 동작을 그만하는 것은 더 이상 구슬이 움직이지 않을 때 까지이다.

보드의 상태가 주어졌을 때, 최소 몇 번 만에 빨간 구슬을 구멍을 통해 빼낼 수 있는지 구하는 프로그램을 작성하시오.

입력
첫 번째 줄에는 보드의 세로, 가로 크기를 의미하는 두 정수 N, M (3 ≤ N, M ≤ 10)이 주어진다. 다음 N개의 줄에 보드의 모양을 나타내는 길이 M의 문자열이 주어진다. 이 문자열은 '.', '#', 'O', 'R', 'B' 로 이루어져 있다. '.'은 빈 칸을 의미하고, '#'은 공이 이동할 수 없는 장애물 또는 벽을 의미하며, 'O'는 구멍의 위치를 의미한다. 'R'은 빨간 구슬의 위치, 'B'는 파란 구슬의 위치이다.

입력되는 모든 보드의 가장자리에는 모두 '#'이 있다. 구멍의 개수는 한 개 이며, 빨간 구슬과 파란 구슬은 항상 1개가 주어진다.

출력
최소 몇 번 만에 빨간 구슬을 구멍을 통해 빼낼 수 있는지 출력한다. 만약, 10번 이하로 움직여서 빨간 구슬을 구멍을 통해 빼낼 수 없으면 -1을 출력한다.

예제 입력 1
5 5
#####
#..B#
#.#.#
#RO.#
#####
예제 출력 1
1

예제 입력 2
7 7
#######
#...RB#
#.#####
#.....#
#####.#
#O....#
#######
예제 출력 2
5

예제 입력 3
7 7
#######
#..R#B#
#.#####
#.....#
#####.#
#O....#
#######
예제 출력 3
5

예제 입력 4
10 10
##########
#R#...##B#
#...#.##.#
#####.##.#
#......#.#
#.######.#
#.#....#.#
#.#.#.#..#
#...#.O#.#
##########
예제 출력 4
-1

예제 입력 5
3 7
#######
#R.O.B#
#######
예제 출력 5
1

예제 입력 6
10 10
##########
#R#...##B#
#...#.##.#
#####.##.#
#......#.#
#.######.#
#.#....#.#
#.#.##...#
#O..#....#
##########
예제 출력 6
7

예제 입력 7
3 10
##########
#.O....RB#
##########
예제 출력 7
-1
*/
#define SOL (0)
using namespace std;

#ifdef SOL
const int maxn = 10 + 1;
int N, M;

int dr[] = { 1, -1, 0, 0 };
int dc[] = { 0, 0, 1, -1 };

char map[maxn + 1][maxn + 1];
int findFlag = 0;
int cnt = 0xfffe;

typedef struct pos {
	int r, c;
} pos;

pos R;
pos B;

void input()
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			char tmp;
			cin >> tmp;
			map[i][j] = tmp;
			if (tmp == 'R') {
				R.r = i; R.c = j;
			}
			if (tmp == 'B') {
				B.r = i; B.c = j;
			}
		}
	}	
	findFlag = 0;
	cnt = 0xfffe;
}

void show(int cnt)
{
	cout << "============"<< cnt << "============" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << map[i][j] << " ";			
		}
		cout << endl;
	}
	cout << "============" << endl;
}

pos findNewPos(pos cur, int dic, char col)
{	
	pos pre = cur;
	while (1) {
		cur.r += dr[dic];
		cur.c += dc[dic];

		if ((map[cur.r][cur.c] == '#' || \
			map[cur.r][cur.c] == 'R' || \
			map[cur.r][cur.c] == 'B')) {
			cur.r -= dr[dic];
			cur.c -= dc[dic];
			break;
		}
		else if (map[cur.r][cur.c] == 'O') {
			cur.r = maxn; cur.c = maxn;
			findFlag = 1;			
			break;
		}
	}

	if (cur.r != maxn) {
		map[pre.r][pre.c] = '.';
		map[cur.r][cur.c] = col;
	}
	else {
		map[pre.r][pre.c] = '.';
	}
	
	return cur;
}

void DFS(pos red, pos blue, int preDir, int ballCnt)
{	
	if (ballCnt > 10)	return;
	if (ballCnt > cnt && cnt != -1)	return;
	//show(ballCnt);

	preDir = preDir % 2 ? preDir - 1 : preDir + 1;
	for (int i = 0; i < 4; i++) {
		int dfsFlag = 1;
		int dir = i;
		
		if (preDir == dir) continue;		
		if (!(map[red.r + dr[dir]][red.c + dc[dir]] == '.' || (map[red.r + dr[dir]][red.c + dc[dir]] == 'O')) && \
			!(map[blue.r + dr[dir]][blue.c + dc[dir]] == '.') )continue;

		pos nRed;
		pos nBlue;

		if ((dir == 0 && red.r > blue.r) || (dir == 1 && red.r < blue.r)) {
			nRed = findNewPos(red, dir, 'R');
			nBlue = findNewPos(blue, dir, 'B');
		}
		else if ((dir == 0 && red.r < blue.r) || (dir == 1 && red.r > blue.r)) {
			nBlue = findNewPos(blue, dir, 'B');
			nRed = findNewPos(red, dir, 'R');
		}
		else if ((dir == 2 && red.c < blue.c) || (dir == 3 && red.c > blue.c)) {
			nBlue = findNewPos(blue, dir, 'B');
			nRed = findNewPos(red, dir, 'R');			
		}
		else if ((dir == 2 && red.c > blue.c) || (dir == 3 && red.c < blue.c)) {		
			nRed = findNewPos(red, dir, 'R');
			nBlue = findNewPos(blue, dir, 'B');
		}
		else {
			nBlue = findNewPos(blue, dir, 'B');
			nRed = findNewPos(red, dir, 'R');			
		}

		if (nRed.r == maxn && nBlue.r == maxn) {
			dfsFlag = 0;
			if (cnt == 0xfffe) cnt = -1;
		}
		else if (nBlue.r == maxn) {
			dfsFlag = 0;
		}		
		else if (nRed.r == maxn) {
			dfsFlag = 0;
			if (cnt != -1) cnt = cnt > ballCnt ? ballCnt : cnt;
			else cnt = ballCnt;
		}

		if (dfsFlag) {
			DFS(nRed, nBlue, dir, ballCnt + 1);
		}

		if (nRed.r == maxn && nBlue.r == maxn) {
			map[red.r][red.c] = 'R';
			map[blue.r][blue.c] = 'B';
		}
		else {
			if (red.r == nRed.r && red.c == nRed.c) {
				map[red.r][red.c] = 'R';
			}
			else {
				map[red.r][red.c] = 'R';
				map[nRed.r][nRed.c] = '.';
			}

			if (blue.r == nBlue.r && blue.c == nBlue.c) {
				map[blue.r][blue.c] = 'B';
			}
			else {
				map[blue.r][blue.c] = 'B';
				map[nBlue.r][nBlue.c] = '.';
			}
		}		
	}
}

int main()
{
	int T = 1;
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);
	
	freopen("BAEKJOON_13460.txt", "r", stdin);
	cin >> T;

	for (int i = 0; i < T; i++) {
		cin >> N >> M;
		input();
		DFS(R, B, -1, 1);
		cnt = cnt > 10 ? -1 : cnt;
		cout << cnt << endl;
	}	

	return 0;
}

#else
#include <cstdio>

struct INFO{
	int rx, ry, bx, by, d, cnt;
};

char map[10][10];
int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

int main() {
	int N, M;
	scanf("%d %d", &N, &M);
	int rx, ry, bx, by;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf(" %c", &map[i][j]);
			if (map[i][j] == 'R') {
				rx = i, ry = j, map[i][j] = '.';
			}
			else if (map[i][j] == 'B') {
				bx = i, by = j, map[i][j] = '.';
			}
		}
	}

	int idx = 0, now = 0;
	INFO info[1 << 11];
	info[idx++] = { rx, ry, bx, by, -1, 1 };

	while (now < idx) {
		rx = info[now].rx;
		ry = info[now].ry;
		bx = info[now].bx;
		by = info[now].by;
		int d = info[now].d;
		int cnt = info[now++].cnt;
		if (cnt > 10) break;
		for (int i = 0; i < 4; i++) {
			if (d == i || d == (i ^ 1)) continue;
			int nrx = rx, nry = ry, nbx = bx, nby = by, rcnt = 0, bcnt = 0;
			while (map[nrx][nry] == '.')
				nrx += dx[i], nry += dy[i], rcnt++;
			while (map[nbx][nby] == '.')
				nbx += dx[i], nby += dy[i], bcnt++;

			if (map[nbx][nby] == 'O') continue;
			if (map[nrx][nry] == 'O') {
				printf("%d", cnt); return 0;
			}

			nrx -= dx[i]; nry -= dy[i];
			nbx -= dx[i]; nby -= dy[i];

			if (nrx == nbx && nry == nby) {
				if (rcnt > bcnt)
					nrx -= dx[i], nry -= dy[i];
				else
					nbx -= dx[i], nby -= dy[i];
			}
			if (rx == nrx && ry == nry && bx == nbx && by == nby) continue;
			info[idx++] = { nrx,nry,nbx,nby,i,cnt + 1 };
		}
	}
	puts("-1");
	return 0;
}

#endif