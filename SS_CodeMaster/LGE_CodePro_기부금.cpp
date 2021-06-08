#include <iostream>
using namespace std;

int N;//직원 수
int M;//기부금 총액
int A[1000010];//직원 별 성과급'

int input_data() {
	int i, max = 0;
	cin >> N >> M;
	for (i = 0; i < N; i++) {
		cin >> A[i];
		if (max < A[i]) max = A[i];
	}
	return max;
}

int check(int h) {
	int i, sum = M;
	for (i = 0; i < N; i++) {
		if (h < A[i]) {
			sum -= A[i] - h;
			if (sum <= 0) return 1;
		}
	}
	return 0;
}
int solve(int max) {
	int s = 0, e = max, m, sol = 0;
	while (s <= e) {
		m = (s + e) / 2;
		if (check(m) == 1) {
			sol = m; s = m + 1;
		}
		else e = m - 1;
	}
	return sol;
}
int main() {
	int max = input_data();
	int ans = solve(max);
	cout << ans << endl;
	return 0;
}
