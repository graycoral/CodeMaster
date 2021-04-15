#include <iostream>

/*
https://www.acmicpc.net/problem/13460
����
��ŸƮ��ũ���� �Ǹ��ϴ� ��̿� �峭�� �߿��� ���� �αⰡ ���� ��ǰ�� ���� Ż���̴�. ���� Ż���� ���簢�� ���忡 ���� ������ �Ķ� ������ �ϳ��� ���� ����, ���� ������ ������ ���� ������ �����̴�.

������ ���� ũ��� N, ���� ũ��� M�̰�, ���ǻ� 1��1ũ���� ĭ���� �������� �ִ�. ���� �ٱ� ��� ���� ��� ������ �ְ�, ���忡�� ������ �ϳ� �ִ�. ���� ������ �Ķ� ������ ũ��� ���忡�� 1��1ũ���� ĭ�� ���� ä��� �������̰�, ���� �ϳ��� �� �ִ�. ������ ��ǥ�� ���� ������ ������ ���ؼ� ������ ���̴�. �̶�, �Ķ� ������ ���ۿ� ���� �� �ȴ�.

�̶�, ������ ������ �ǵ帱 ���� ����, �߷��� �̿��ؼ� �̸� ���� ������ �Ѵ�. �������� ����̱�, ���������� ����̱�, �������� ����̱�, �Ʒ������� ����̱�� ���� �� ���� ������ �����ϴ�.

������ ���ۿ��� ���� ���ÿ� �����δ�. ���� ������ ���ۿ� ������ ����������, �Ķ� ������ ���ۿ� ������ �����̴�. ���� ������ �Ķ� ������ ���ÿ� ���ۿ� ������ �����̴�. ���� ������ �Ķ� ������ ���ÿ� ���� ĭ�� ���� �� ����. ��, ���� ������ �Ķ� ������ ũ��� �� ĭ�� ��� �����Ѵ�. ����̴� ������ �׸��ϴ� ���� �� �̻� ������ �������� ���� �� �����̴�.

������ ���°� �־����� ��, �ּ� �� �� ���� ���� ������ ������ ���� ���� �� �ִ��� ���ϴ� ���α׷��� �ۼ��Ͻÿ�.

�Է�
ù ��° �ٿ��� ������ ����, ���� ũ�⸦ �ǹ��ϴ� �� ���� N, M (3 �� N, M �� 10)�� �־�����. ���� N���� �ٿ� ������ ����� ��Ÿ���� ���� M�� ���ڿ��� �־�����. �� ���ڿ��� '.', '#', 'O', 'R', 'B' �� �̷���� �ִ�. '.'�� �� ĭ�� �ǹ��ϰ�, '#'�� ���� �̵��� �� ���� ��ֹ� �Ǵ� ���� �ǹ��ϸ�, 'O'�� ������ ��ġ�� �ǹ��Ѵ�. 'R'�� ���� ������ ��ġ, 'B'�� �Ķ� ������ ��ġ�̴�.

�ԷµǴ� ��� ������ �����ڸ����� ��� '#'�� �ִ�. ������ ������ �� �� �̸�, ���� ������ �Ķ� ������ �׻� 1���� �־�����.

���
�ּ� �� �� ���� ���� ������ ������ ���� ���� �� �ִ��� ����Ѵ�. ����, 10�� ���Ϸ� �������� ���� ������ ������ ���� ���� �� ������ -1�� ����Ѵ�.

���� �Է� 1
5 5
#####
#..B#
#.#.#
#RO.#
#####
���� ��� 1
1

���� �Է� 2
7 7
#######
#...RB#
#.#####
#.....#
#####.#
#O....#
#######
���� ��� 2
5

���� �Է� 3
7 7
#######
#..R#B#
#.#####
#.....#
#####.#
#O....#
#######
���� ��� 3
5

���� �Է� 4
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
���� ��� 4
-1

���� �Է� 5
3 7
#######
#R.O.B#
#######
���� ��� 5
1

���� �Է� 6
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
���� ��� 6
7

���� �Է� 7
3 10
##########
#.O....RB#
##########
���� ��� 7
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