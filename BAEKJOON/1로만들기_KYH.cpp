#include <iostream>
using namespace std;

int minNum = 0x7ffff;

void DFS(int num, int cnt)
{
	if (minNum < cnt)	return;
	if (num == 0)	return;
	if (num == 1) {
		minNum = cnt;
		return;
	}

	if (num % 3 == 0) DFS(num / 3, cnt + 1);
	if (num % 2 == 0) DFS(num / 2, cnt + 1);
	DFS(num - 1, cnt + 1);
}

int main()
{
	int N = 0;
	cin >> N;
	DFS(N, 0);
	cout << minNum;
	return 0;
}