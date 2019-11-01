#include <stdio.h>
#define MAXN	((int)5e3+2)
#define IMP (100 * 100 + 10)

int N, M;//���� ��, ���� ���� ��
int A[5000], B[5000], D[5000];//���� A, ���� B, �Ÿ� D

int map[MAXN][MAXN];
int q[MAXN];
int path[MAXN];
int wp, rp;

void InputData() {
	int i;

	scanf("%d %d", &N, &M);
	for (i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			map[i][j] = IMP;
		}
	}
	for (i = 0; i < M; i++) {
		scanf("%d %d %d", &A[i], &B[i], &D[i]);
		map[A[i]][B[i]] = map[B[i]][A[i]] = D[i];
	}
}

int pop() { return	q[rp++]; }
int empty() { return wp == rp; }

void push(int n, int t)
{
	if (path[n] <= t)	return;
	path[n] = t;
	q[wp++] = n;
}

int BFS(int s)
{
	int max = 0;
	rp = wp = 0;
	for (int i = 1; i <= N; i++) path[i] = IMP;

	push(s, 0);
	while (!empty())
	{
		int cur = pop();
		for (int i = 1; i <= N; i++) {
			push(i, path[cur] + map[cur][i]);
		}
	}

	for (int i = 1; i <= N; i++) {
		if (max < path[i])	max = path[i];
	}
	//printf("S : %d , MAX : %d\n", s, max);
	return max;
}

int sol()
{
	int i, j;

	int min = 0x7ffff;

	for (int i = 1; i <= N; i++) {
		int ret = BFS(i);
		if (min > ret)	min = ret;
	}

	return min;
}

int main() {
	int ans = -1;
	InputData();//	�Է� �Լ�
	ans = sol();
	//	�ڵ带 �ۼ��ϼ���

	printf("%d\n", ans);//	���� ���
	return 0;
}
