#include <iostream>

using namespace std;

const int max_num = 20 + 1;

int N, K;
int num[max_num];

void input()
{
	for (int i = 0; i < N; i++) {
		num[i] = 0;
	}

	cin >> N >> K;
	for (int i = 0; i < N; i++) {
		cin >> num[i];
	}
}

int sol()
{
	for (int i = 0; i < 1<<N; i++) {
		int sum = 0;
		for (int j = 0; j < N; j++) {
			if (i & (1 << j)) {
				sum += num[j];
			}
		}
		if (sum == K)	return 1;
	}

	return 0;
}

int main()
{
	int test_case = 1;
	const char* y = "YES";
	const char* n = "NO";

	cin >> test_case;
	for (int i = 0; i < test_case; i++) {
		input();
		cout << ((sol() == 1) ? y : n) << endl;
	}
	return 0;
}