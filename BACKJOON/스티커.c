#include <stdio.h>
#include <stdlib.h>
#define MAXN	((int)1e5+10)

int T, n;
int data[3][MAXN];
int dp[3][MAXN];
int Sol[MAXN];

int cnt;

void input()
{
	scanf("%d", &n);

	for (int i = 1; i <= 2; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%d", &data[i][j]);
		}
	}
}

int max(int a, int b, int c)
{
	return a > b ? (a > c ? a : c) : (b > c ? b : c);
}

void print()
{
	printf("\n");
	for (int i = 1; i <= 2; i++) {
		for (int j = 1; j <= n; j++) {
			printf("%5d", dp[i][j]);
		}
		printf("\n");
	}
}

void sol()
{
	int maxNum = 0;
	memset(dp, 0, sizeof(dp));

	dp[1][1] = data[1][1];
	dp[2][1] = data[2][1];

	for (int i = 2; i <= n; i++) {
		for (int j = 1; j <= 2; j++) {
			int maxnum = 0;
			if (j % 2 == 1)
				maxnum = max(dp[j][i - 2], dp[j + 1][i - 2], dp[j + 1][i - 1]);
			else
				maxnum = max(dp[j][i - 2], dp[j - 1][i - 2], dp[j - 1][i - 1]);
			dp[j][i] += maxnum + data[j][i];
			if (maxNum < dp[j][i])	maxNum = dp[j][i];
			//print();
		}
	}
	printf("%d\n", maxNum);
}

int main()
{
	scanf("%d", &T);
	for (int i = 0; i < T; i++) {
		input();
		sol();
	}
	return 0;
}