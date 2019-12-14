#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
int M, S, C;

vector<int> diff;
vector<int> Data;
void input()
{
	int input;
	cin >> M >> S >> C;
	for (int i = 0; i < C; i++) {
		cin >> input;
		Data.push_back(input);
	}
}

void sol()
{
	int sum = 0;
	sort(Data.begin(), Data.end());

	for (int i = 0; i < C - 1; i++) {
		diff.push_back(Data[i + 1] - Data[i]);
	}
	for (auto Diff : diff) {
		sum += Diff;
	}
	sort(diff.begin(), diff.end(), greater<int>());

	for (int i = 0; i < M - 1 && i < C - 1; i++) {
		sum -= diff[i];
		sum++;
	}
	cout << ++sum;
}

int main()
{
	input();
	sol();
	return 0;
}