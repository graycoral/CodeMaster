#include <iostream>

using namespace std;

int main()
{
	int test_case;

	cin >> test_case;	
	for (int i = 1; i <= test_case; i++) {
		int score[101] = { 0, };
		int ans = 0; int ansNum = 0;
		int tmptestcase;
		cin >> tmptestcase;
		for (int j = 0; j < 1000; j++) {
			int tmp;
			cin >> tmp;
			score[tmp]++;
			if (ans < score[tmp]) {
				ans = score[tmp];
				ansNum = tmp;
			}
			else if (ans == score[tmp]) {
				if (ansNum < tmp) {
					ans = score[tmp];
					ansNum = tmp;
				}
			}
		}
		cout << "#" << i << " " << ansNum << endl;
	}

	return 0;
}