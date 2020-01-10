#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
int W;
int maxCnt;
vector<int> usedCoin;
vector<int> Coin;

int coinList[6] = { 500, 100, 50, 10, 5, 1 };

void input()
{
	cin >> W;
	for (int i = 0; i < 6; i++) {
		int c;
		cin >> c;
		Coin.push_back(c);
		usedCoin.push_back(0);
	}
}

void sol()
{
	int idx = 5;
	int nW = W;

	for (int i = 5; i >= 0; i--) {
		if (i == 0) {
			maxCnt += W / coinList[0];
			usedCoin[0] = W / coinList[0];
			break;
		}
		for (int j = Coin[i]; j >= 0; j--) {
			if ((W - (j * coinList[i])) % coinList[i - 1] == 0) {
				W -= j * coinList[i];
				usedCoin[i] = j;
				maxCnt += j;
				break;
			}
		}
		if (W == 0) break;
	}

	cout << maxCnt << endl;
	for (auto n : usedCoin) {
		cout << n << " ";
	}
}

int main()
{
	input();
	sol();
	return 0;
}
