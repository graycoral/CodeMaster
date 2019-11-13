#include <iostream>
using namespace std;

int N;//지도 크기
char map[110][110];//지도 정보

#define IMP (1<<29)
struct Q {
	int r, c;
};
struct Q q[100 * 100 * 100];
int wp, rp;
int v[110][110];

void Input_Data() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> map[i];
	}
}
Q pop() { return q[rp++]; }
int empty() { return wp == rp; }
void push(int r, int c, int sum)
{
	if (v[r][c] > sum) {
		v[r][c] = sum;
		q[wp].r = r;
		q[wp++].c = c;
	}
	/*
	if (v[r][c] < sum)	return;\


	v[r][c] = sum;
	q[wp].r = r;
	q[wp++].c = c;

	*/
}

int sol()
{
	int rr[] = { -1, 1, 0, 0 };
	int cc[] = { 0,  0, -1, 1 };

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			v[i][j] = IMP;
		}
	}
	//push(0, 0, 0);
	q[wp].r = 0; q[wp++].c = 0;
	v[0][0] = 0;
	while (!empty()) {
		Q d = q[rp++];
		for (int i = 0; i < 4; i++) {
			int nr = d.r + rr[i]; int nc = d.c + cc[i];
			if ((nr < 0) || (nr >= N) || (nc < 0) || (nc >= N)) continue;//범위 벗어남
			push(nr, nc, v[d.r][d.c] + map[nr][nc] - '0');
		}
	}
	return v[N - 1][N - 1];
}

int main() {
	int ans = -1;
	Input_Data();		//	입력 함수
	//	코드를 작성하세요
	ans = sol();
	cout << ans << endl;	//	정답 출력
	return 0;
}

