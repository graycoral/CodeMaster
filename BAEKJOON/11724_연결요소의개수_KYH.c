#include <stdio.h>
#define MAXN	((int)1000+10)
int N, M;
int map[MAXN][MAXN];
int v[MAXN];
int q[MAXN * 100];
int cnt, wp, rp;

void input()
{
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= M; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		map[u][v] = 1;
		map[v][u] = 1;
	}
}

int pop() { return q[wp++]; }
int empty() { return wp == rp; }

void push(int idx) {
	//printf("%d -> ", idx);
	v[idx] = 1;
	q[rp++] = idx;
}

void sol(int idx)
{
	if (v[idx] == 1)	return;
	push(idx);
	cnt++;
	while (!empty()) {
		int cur = pop();
		for (int i = 1; i <= N; i++) {
			if (map[cur][i] == 1 && v[i] == 0) {
				push(i);
			}
		}
	}
	//printf("\n");
}

int main()
{
	input();
	for (int i = 1; i <= N; i++) {
		sol(i);
	}

	printf("%d", cnt);
	return 0;
}