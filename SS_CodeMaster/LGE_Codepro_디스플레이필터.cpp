#include <iostream>
#include <algorithm>
using namespace std;

int N;	// 필터의 수
int R[11]; // 반사의 정도
int P[11]; // 투과의 정도
int diff = 987654321, cnt;

void InputData(void) {
	cin >> N;
	for (int i = 1; i <= N; i++)  cin >> R[i] >> P[i];
}

int sol()
{
	for (int i = 0; i < (1 << N); i++) {
		int p = 0, r = 1, tmpCnt = 0;
		for (int j = 0; j < N; j++) {
			if (i & (1 << j)) {
				p += P[j]; r *= R[j];
				tmpCnt++;
			}
		}
		int tmpDiff = abs(p - r);
		if (diff > tmpDiff) {
			diff = tmpDiff;
			cnt = tmpCnt;
		}
		else if (diff == tmpDiff) {
			if (cnt < tmpCnt)	cnt = tmpCnt;
		}
	}

	return N - cnt;
}


int main() {
	int ans = -1;
	InputData(); // 입력함수

	// 코드를 작성 하세요
	ans = sol();
	cout << ans << endl;//출력
	return 0;
}

