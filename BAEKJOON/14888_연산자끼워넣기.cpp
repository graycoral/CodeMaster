#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;
const int maxn = 101;

int N;
long long int num[maxn];
int cal[4];
long long int maxSum = -1000000000;
long long int minSum = 1000000000;


void calSum(long long int sum, int nextIdx)
{
	if (nextIdx >= N) {
		maxSum = maxSum < sum ? sum : maxSum;
		minSum = minSum > sum ? sum : minSum;
	}

	for (int i = 0; i < 4; i++) {
		long long int preSum = sum;
		if (cal[i] == 0) continue;
		cal[i]--;
		if (i == 0) {
			sum += num[nextIdx];
			calSum(sum, nextIdx + 1);
		}
		else if (i == 1) {
			sum -= num[nextIdx];
			calSum(sum, nextIdx + 1);
		}
		else if (i == 2) {
			sum *= num[nextIdx];
			calSum(sum, nextIdx + 1);
		}
		else if (i == 3) {
			sum /= num[nextIdx];
			calSum(sum, nextIdx + 1);
		}
		cal[i]++;
		sum = preSum;
	}
}

int main()
{
	//freopen("14888_연산자끼워넣기.txt", "r", stdin);
	int T = 1;
	//cin >> T;

	for (int i = 0; i < T; i++) {
		long long int tmp;
		maxSum = -1000000000;
		minSum = 1000000000;
		cin >> N;
		for (int j = 0; j < N; j++) {
			cin >> tmp;
			num[j] = tmp;
		}

		for (int calIdx = 0; calIdx < 4; calIdx++) {
			int tmpcal;
			cin >> tmpcal;
			cal[calIdx] = tmpcal;
		}

		calSum(num[0], 1);

		cout << maxSum << endl;
		cout << minSum << endl;
	}
	return 0;
}