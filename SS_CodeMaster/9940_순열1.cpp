#include<iostream>
#include<string>
#include<cstring>

using namespace std;

int N;
int used[100000 + 1];
int ans;

void input()
{
	ans = 1;
	cin >> N;
	for (int i = 0; i < N; i++) {
		int tmp;
		cin >> tmp;

		if (used[tmp]) {
			ans = 0;
		}
		else
		{
			used[tmp] = 1;
		}
		
	}
}

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int test_case;
	int T;

	freopen("9940_input.txt", "r", stdin);
	cin >> T;
	/*
	   ���� ���� �׽�Ʈ ���̽��� �־����Ƿ�, ������ ó���մϴ�.
	*/
	for (test_case = 1; test_case <= T; ++test_case)
	{
		string tmp;
		memset(used, 0, sizeof(used));
		input();
		if (ans) {
			tmp = " Yes";
		}
		else {
			tmp = " No";
		}
		cout << "#" << test_case << tmp.c_str()<< endl;
		

	}
	return 0;//��������� �ݵ�� 0�� �����ؾ��մϴ�.
}