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

	InputData();// �Է¹޴� �κ�

	// ���⼭���� �ۼ�

	cout << ans << endl;// ����ϴ� �κ�
	return 0;
}