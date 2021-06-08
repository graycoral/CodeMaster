#include <iostream>

using namespace std;

const int max_num = 200 + 1;
const int dr[] = { 0, 0, 1, -1 };
const int dc[] = { 1, -1, 0, 0 };
char order[max_num][max_num];
int visitied[max_num][max_num][4][16];
int R, C;
int mem;

typedef struct Queue {
	int r, c;
	int dic, mem;
} Queue;

Queue q[max_num * max_num];
int front;
int last;
int checkFlag = 0;

void input()
{
	for (int i = 0; i < max_num; i++) {
		for (int j = 0; j < max_num; j++) {
			order[i][j] = 0;
		}
	}

	for (int i = 0; i < max_num * max_num; i++) {
		q[i].r = q[i].c = q[i].dic = q[i].mem = 0;
	}

	for (int i = 0; i < max_num; i++) {
		for (int j = 0; j < max_num; j++) {
			for (int d = 0; d < 4; d++) {
				for (int m = 0; m < 16; m++) {
					visitied[i][j][d][m] = 0;
				}
			}
		}
	}
	front = last = mem = checkFlag = 0;

	cin >> R >> C;
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			cin >> order[i][j];
			if (order[i][j] == '@') {
				checkFlag = 1;
			}
		}
	}
}

void push(int r, int c, int dic, int mem)
{
	visitied[r][c][dic][mem] = 1;
	q[front].r = r;
	q[front].c = c;
	q[front].dic = dic;
	q[front++].mem = mem;
}

Queue pop() {
	return q[last++];
}

int empty()
{
	return (front == last ? 1 : 0);
}

int BFS()
{
	push(1, 1, 0, 0);
	while (!empty()) {
		Queue cur = pop();

		int r = cur.r; int c = cur.c; int d = cur.dic; int mem = cur.mem;

		if (order[r][c] == '@')			return 1;

		if (order[r][c] >= '0' && order[r][c] <= '9') {
			mem = order[r][c] - '0';
		}
		else if (order[r][c] == '<') d = 1;
		else if (order[r][c] == '>') d = 0;
		else if (order[r][c] == '^') d = 3;
		else if (order[r][c] == 'v') d = 2;
		else if (order[r][c] == '_') d = (mem == 0 ? 0 : 1);
		else if (order[r][c] == '|') d = (mem == 0 ? 2 : 3);
		else if (order[r][c] == '.') {		}
		else if (order[r][c] == '+') mem = (mem >= 15 ? 0 : mem + 1);
		else if (order[r][c] == '-') mem = (mem <= 0 ? 15 : mem - 1);
		
		r += dr[d]; c += dc[d];
		if (r > R) r = 1;
		if (r <= 0)	r = R;
		if (c > C) c = 1;
		if (c <= 0) c = C;

		if (order[r][c] == '?') {
			for (int i = 0; i < 4; i++) {
				if (visitied[r][c][i][mem] == 0) {
					push(r, c, i, mem);
				}
			}
		}
		else {
			if (visitied[r][c][d][mem] == 0) {
				push(r, c, d, mem);
			}
		}
	}

	return 0;
}

void sol(int tc)
{
	if (checkFlag == 1 && BFS() == 1) {
	//if (BFS() == 1) {
		cout << "#" << tc << " " << "YES" << endl;
	}
	else {
		cout << "#" << tc << " " << "NO" << endl;
	}
}

int main()
{
	int test_case = 1;
	freopen("1824_input.txt", "r", stdin);
	cin >> test_case;

	for (int i = 1; i <= test_case; i++) {
		input();
		sol(i);
	}
	return 0;
}