#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int dp[301], dp1[301], dp2[301];

int main()
{
	int N;
	cin >> N;
	vector<int> Step;
	for (int i = 0; i < N; ++i) {
		int tmp;
		cin >> tmp;
		Step.push_back(tmp);
	}

	int cnt = 0;
	dp1[0] = Step[0];
	dp1[1] = dp1[0]+ Step[1];

	dp2[1] = Step[1];

	dp[0] = max(dp1[0], dp2[0]);
	dp[1] = max(dp1[1], dp2[1]);

	cnt = 2;

	for (int i = 2; i < N; i++) {
		if (cnt >= 2) {	dp1[i] = Step[i] + dp2[i - 1];	}
		else {	dp1[i] = Step[i] + dp[i - 1]; }

		dp2[i] = Step[i] + dp[i - 2];

		if (dp1[i] > dp2[i]) cnt = 2;
		else cnt = 1;
		dp[i] = max(dp1[i], dp2[i]);
	}
	cout << dp[N - 1] << endl;


	return 0;
}