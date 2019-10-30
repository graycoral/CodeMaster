#include <stdio.h>
#include <stdlib.h>

#define MAXN    ((int)5e2+10)
#define SOL     (1)
int N;
int maxcnt = 1;

struct room {
	int idx, s, e;
};

struct room R[MAXN];
int tmp[MAXN];
int sol[MAXN];
int mark[MAXN];
int visted[MAXN];

void input()
{
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d %d %d", &R[i].idx, &R[i].s, &R[i].e);
	}
}

// 오름차순으로 정렬할 때 사용하는 비교함수
int comp(const void* a, const void* b) {
	struct room* x = a, * y = b;
	return x->e - y->e;
}

void Sol()
{
	int end = 0;

	end = R[0].e;
	sol[0] = R[0].idx;
	for (int i = 0; i < N; i++) {
		if (end <= R[i].s) {
			end = R[i].e;
			sol[maxcnt++] = R[i].idx;
		}
	}
}

int main()
{
	input();
	qsort(R, N, sizeof(R[0]), comp);
	Sol();

	printf("%d\n", maxcnt);
	for (int i = 0; i < maxcnt; i++) {
		printf("%d ", sol[i]);
	}

	return 0;
}