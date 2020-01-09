#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int N;
vector<pair<int, int>> Data;

void input()
{
	cin >> N;
	for (int i = 0; i < N; i++) {
		int T, L;
		cin >> T >> L;
		Data.push_back(make_pair(T, T + L - 1));
	}
	sort(Data.begin(), Data.end());
}

void sol()
{
	int cnt = 1;
	int e = Data[0].second;

	for (int i = 1; i < N; i++) {
		if (e < Data[i].first) {
			cnt++;
			e = Data[i].second;
		}

		if (e > Data[i].second)	e = Data[i].second;
	}

	cout << cnt;
}

int main()
{
	input();
	sol();
	return 0;
}