#include <iostream>
#include <algorithm>
#define MAXN	((int)90 +11)

using namespace std;

int N;
int v[MAXN];
int d[MAXN];
int cnt;
long long int dp[MAXN];

void DFS(int idx, int prev)
{
	if (idx == N) {
		for (int i = 0; i < N; i++) {
			cout << d[i] << " ";
		}
		cout << endl << ": " << cnt << endl;
		cnt++;
		return;
	}
	if (v[idx] == 1)	return;
	d[idx] = prev;
	v[idx] = 1;
	if (prev == 1) {
		DFS(idx + 1, 0);
	}
	else {
		DFS(idx + 1, 0);
		DFS(idx + 1, 1);
	}
	v[idx] = 0;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N;
	//DFS(0, 1); /* DFS로 풀어보기 */
	dp[0] = 0; dp[1] = 1;
	for (int i = 2; i <= N; i++) {
		dp[i] = dp[i - 2] + dp[i - 1];
	}

	cout << dp[N];
	return 0;
}