#include <stdio.h>
#define MAXN    ((int)1e5+10)

int N, K;
int V[1001], W[1001];
int D[1001][10001];

void input()
{
	scanf("%d %d", &N, &K);
	for (int i = 1; i <= N; i++) {
		scanf("%d %d", &W[i], &V[i]);
	}
}

int main()
{
	input();

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= K; j++) {
			if (j >= W[i])   D[i][j] = (D[i - 1][j] > D[i - 1][j - W[i]] + V[i]) ? D[i - 1][j] : D[i - 1][j - W[i]] + V[i];
			else            D[i][j] = D[i - 1][j];
		}
	}

	printf("%d", D[N][K]);
	return 0;
}