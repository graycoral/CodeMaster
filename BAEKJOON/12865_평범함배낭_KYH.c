#include <stdio.h>
#define MAXN	((int)1e5+10)

int N, K;
int V[101], W[101];
int D[101][1000001];

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
#if 1
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= K; j++) {
			D[i][j] = D[i - 1][j]; // ?????
			if (j >= W[i])	D[i][j] = (D[i - 1][j] > D[i - 1][j - W[i]] + V[i]) ? D[i - 1][j] : D[i - 1][j - W[i]] + V[i];
			else			D[i][j] = D[i - 1][j];
		}
	}

	printf("%d", D[N][K]);
#else
	for (int i = 1; i <= N; i++) {
		for (int j = W[i]; j <= K; j++) {
			if (dp[j] < dp[j - W[i]] + V[i]) dp[j] = dp[j - W[i]] + V[i];
		}

	}
	printf("%d", dp[K]);
#endif
	return 0;
}