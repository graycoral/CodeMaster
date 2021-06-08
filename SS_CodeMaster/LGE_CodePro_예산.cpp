#include <iostream>
using namespace std;

int N, M;
int A[10000 + 10];
void InputData() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> A[i];
	}
	cin >> M;
}

int main() {
	int ans = -1;

	InputData();// 입력받는 부분

	// 여기서부터 작성

	cout << ans << endl;// 출력하는 부분
	return 0;
}