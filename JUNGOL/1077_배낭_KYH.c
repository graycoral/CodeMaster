#include <stdio.h>
#define MAXN	((int)1e5+10)

int N, K;
int V[MAXN], W[MAXN];
int D[1100][1100];
int dp[MAXN];

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
#if 0
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= K; j++) {
			if (W[i] <= j)	D[i][j] = (D[i - 1][j] > D[i - 1][j - W[i]] + V[i]) ? D[i - 1][j] : D[i - 1][j - W[i]] + V[i];
			else			D[i][j] = D[i - 1][j];
		}
	}

	printf("%d", D[N][K]);
#endif

	for (int i = 1; i <= N; i++) {
		for (int j = W[i]; j <= K; j++) {
			if (dp[j] < dp[j - W[i]] + V[i]) dp[j] = dp[j - W[i]] + V[i];
		}

	}
	printf("%d", dp[K]);
	return 0;
}