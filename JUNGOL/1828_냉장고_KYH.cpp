#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<int, int>> input;
int N;

void Input()
{
	cin >> N;
	for (int i = 0; i < N; i++) {
		int tmp1, tmp2;
		cin >> tmp1 >> tmp2;
		input.push_back(make_pair(tmp1, tmp2));
	}
}

void Sol()
{
	int cnt = 1;
	sort(input.begin(), input.end());
	int s = input[0].first;
	int e = input[0].second;

	for (auto chme : input) {
		if ((s <= chme.first && chme.first <= e) &&
			(e >= chme.second)) {
			s = chme.first;
			e = chme.second;
		}
		else if ((s <= chme.first && chme.first <= e) &&
			(e < chme.second)) {
			s = chme.first;
		}
		else {
			cnt++;
			s = chme.first;
			e = chme.second;
		}
	}
	cout << cnt;
}

int main()
{
	Input();
	Sol();
	return 0;
}