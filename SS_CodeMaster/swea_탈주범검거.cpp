#include <iostream>

using namespace std;

const int max_num = 51;
const int dr[] = { -1, 1, 0, 0 }; // U , D , L , R
const int dc[] = { 0, 0, -1, 1 };
int map[max_num][max_num];
int visted[max_num][max_num];
int N, M;
int startR, startC, L;
int ans = 0;

typedef struct Pos {
	int r, c,t;
} Pos;

Pos q[max_num * max_num];
int front, last;

int direction[8][4] = {
	{-1, -1, -1, -1},	// 0
	{1, 1, 1, 1},		// 1
	{1, 1, -1, -1},		// 2
	{-1, -1, 1, 1},		// 3
	{-1, 1, 1, -1},		// 4
	{1, -1, 1, -1},		// 5
	{1, -1, -1, 1},		// 6
	{-1, 1, -1, 1},		// 7
};

int curDirection[8][4] = {
	{-1, -1, -1, -1},	// 0
	{1, 1, 1, 1},		// 1
	{1, 1, -1, -1},		// 2
	{-1, -1, 1, 1},		// 3
	{1, -1, -1, 1},		// 4
	{-1, 1, -1, 1},		// 5
	{-1, 1, 1, -1},		// 6
	{1, -1, 1, -1},		// 7
};

void input()
{
	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= M; j++) {
			map[i][j] = visted[i][j] = 0;
		}
	}

	front = last = ans = 0;
	cin >> N >> M >> startR >> startC >> L;

	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++) {
			cin >> map[r][c];
		}
	}
}

void push(int r, int c, int t)
{	
	q[front].r = r;
	q[front].t = t;
	q[front++].c = c;
	visted[r][c] = t;
}

Pos pop()
{
	return q[last++];
}

int empty()
{
	return front == last ? 1 : 0;
}

void sol()
{	
	push(startR, startC, 1);
	ans = 1;
	while (!empty()) {
		Pos cur = pop();
		
		if (cur.t >= L)	continue;

		for (int i = 0; i < 4; i++) {
			int nr = cur.r + dr[i];
			int nc = cur.c + dc[i];
			int nt = cur.t + 1;

			if (nr >= N || nc >= M || nr < 0 || nc < 0)    continue;
			if (map[nr][nc] == 0 || visted[nr][nc] > 0)	continue;
			if (curDirection[map[cur.r][cur.c]][i] == -1)	continue;
			if (direction[map[nr][nc]][i] == -1)   continue;
			push(nr, nc, nt);
			if (nt <= L)	ans++;
		}
	}
}

int main()
{
	int test_case = 1;

	//freopen("swea_모의고사_탈주범검거.txt", "r", stdin);
	cin >> test_case;
	for (int i = 1; i <= test_case; i++) {
		input();
		sol();
		cout << "#" << i << " " << ans << endl;
	}
	return 0;
}