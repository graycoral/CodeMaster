#include <iostream>
using namespace std;

#define MAX(a, b) ( a > b ? a : b) 
#define MIN(a, b) ( a > b ? b : a) 
int N;
int A[100 + 10][100 + 10];
int rain[110][110];
int min_num = 100;
int max_num = 0;
int ans = 0;
void InputData() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> A[i][j];
			min_num = MIN(min_num, A[i][j]);
			max_num = MAX(max_num, A[i][j]);
		}
	}
}

const int dr[] = { 1, -1, 0, 0 };
const int dc[] = { 0, 0, 1, -1 };

typedef struct Pos {
	int r, c;
} Pos;

Pos q[101 * 101];

int front, last;
void push(int r, int c)
{
	q[front].r = r;
	q[front++].c = c;
}

Pos pop()
{
	return q[last++];
}

int empty()
{
	return (front == last ? 1 : 0);
}

void sol()
{
	for (int h = min_num; h <= max_num; h++) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (A[i][j] <= h) rain[i][j] = h;
				else rain[i][j] = 0;
			}
		}

		int cnt = 0;
		for (int r = 0; r < N; r++) {
			for (int c = 0; c < N; c++) {
				if (rain[r][c])	continue;
				front = last = 0;
				push(r, c);
				rain[r][c] = ++cnt;
				while (!empty()) {
					Pos cur = pop();
					for (int k = 0; k < 4; k++) {
						int nr = cur.r + dr[k];
						int nc = cur.c + dc[k];
						if (nr < 0 || nc < 0 || nr >= N || nc >= N)	continue;
						if (rain[nr][nc])	continue;
						push(nr, nc);
						rain[nr][nc] = cnt;
					}
				}
			}
		}
		ans = MAX(ans, cnt);
	}
	
}

int main() {
	//freopen("A2_input.txt", "r", stdin);
	InputData();// 입력받는 부분
	sol();
	cout << ans << endl;// 출력하는 부분
	return 0;
}