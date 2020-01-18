#include <iostream>
#include <algorithm>

using namespace std;

int N;
long long int dp[100010];
long long int divNum = 20100529;

void Sol()
{
	cin >> N;
	dp[1] = 1; dp[2] = 3;

	for (int i = 3; i <= N; i++) {
		dp[i] = (dp[i - 1] + (2 * dp[i - 2])) % divNum;
	}
	cout << dp[N] << endl;
}

int main()
{
	Sol();
	return 0;
}