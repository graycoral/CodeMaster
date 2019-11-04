#include <stdio.h>
#define MAXN	((int)1e9+10)
int N, K;
int coin[10 + 2];

void input()
{
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; i++) {
		scanf("%d", &coin[i]);
	}

}

int  sol()
{
	int reVal = 0;

	while (K) {
		for (int i = N - 1; i >= 0; i--) {
			reVal += K / coin[i];
			K %= coin[i];
		}
	}
	return reVal;
}

int main()
{
	int ans = -1;
	input();
	ans = sol();
	printf("%d", ans);
	return 0;
}