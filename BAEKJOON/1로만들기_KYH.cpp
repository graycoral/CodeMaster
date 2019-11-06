#if 1
#include <iostream>
#include <algorithm>

#define MAXN	((int)1000001)
using namespace std;

int N;
int d[MAXN];

int main()
{
	cin >> N;
	fill(d, d + MAXN, MAXN);

	d[1] = 0;
	for (int i = 1; i < N; i++) {
		d[i + 1] = min(d[i + 1], d[i] + 1);
		if (i * 2 < MAXN) d[i * 2] = min(d[i * 2], d[i] + 1);
		if (i * 3 < MAXN) d[i * 3] = min(d[i * 3], d[i] + 1);
	}
	cout << d[N];

	return 0;
}
#else
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
#endif