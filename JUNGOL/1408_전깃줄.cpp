#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int N;
vector<pair<int, int>> Data;
int D[110];

void Input()
{
	cin >> N;
	for (int i = 0; i < N; i++) {
		int tmp1, tmp2;
		cin >> tmp1 >> tmp2;
		Data.push_back(make_pair(tmp1, tmp2));
	}
}

void Sol()
{
	int len = 0;

	sort(Data.begin(), Data.end());
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < i; j++) {
			if ((Data[i].second > Data[j].second))
				D[i] = max(D[i], D[j] + 1);
		}
		if (len < D[i]) len = D[i];
	}

	cout << N - len - 1;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	Input();
	Sol();

	return 0;
}