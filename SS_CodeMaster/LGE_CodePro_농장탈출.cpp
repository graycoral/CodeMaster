#include <iostream>

using namespace std;

const int max_num = 20 + 1;

#define MAX(a, b) (a > b ? a : b)

int N;
int cow[max_num];
int ans = 0;
void input()
{
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> cow[i];
	}
}

int checkUp(int a, int b)
{
	while (a != 0 && b != 0) {
		if ((((a % 10) + (b % 10)) / 10) == 1) return 0;
		else {
			a /= 10; b /= 10;
		}
	}
	
	return 1;
}

void sol()
{
	for (int i = 0; i < (1 << N); i++) {
		int cnt = 0;
		int sum = 0;
		int changeFlag = 1;
		for (int j = 0; j < N; j++) {
			if (i & (1 << j)) {
				cout << j << " ";
				if (checkUp(sum, cow[j])) {
					//cout << cow[j] << " ";
					sum += cow[j];
					cnt++;
				}
				else {
					changeFlag = 0;
					break;
				}
			}
		}
		cout << endl;
		if(changeFlag) ans = MAX(ans, cnt);
		changeFlag = 1;
	}
}

int main()
{
	input();
	sol();
	cout << ans << endl;
	return 0;
}