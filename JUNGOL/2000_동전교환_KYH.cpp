#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define MAXN	((int)64010)
#define INF		((int)0x7ffffff)

int N, W;
vector<int> coin;
int dp[MAXN];

void input()
{
	cin >> N;
	for (int i = 0; i < N; i++) {
		int m;
		cin >> m;
		coin.push_back(m);
	}
	cin >> W;
}

void sol()
{
	for (int i = 0; i <= W; i++)	dp[i] = INF;
	dp[0] = 0;
	for (int i = 0; i < N; i++) {
		for (int j = coin[i]; j <= W; j++) {
			dp[j] = min(dp[j - coin[i]] + 1, dp[j]);
		}
	}
	if (dp[W] == INF)	cout << "impossible";
	else				cout << dp[W];
}

int main()
{
	input();
	sol();
	return 0;
}