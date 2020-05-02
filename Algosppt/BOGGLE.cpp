#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int N;
char Data[6][6];

int dr[8] = { 1, 1, 1,-1,-1, -1, 0, 0 };
int dc[8] = { 1, 0,-1, 0, 1, -1, -1 ,1 };

void input()
{
	for (int i = 0; i < 5; i++) {
		string tmp;
		cin >> tmp;
		for (int j = 0; j < 5; j++) {
			Data[i][j] = tmp[j];
		}
	}
}

int Find(int r, int c, const string& d)
{
	int retVal = -1;
    if (d.size() == 1) return 1;

	for (int i = 0; i < 8; i++) {
        int nextR = r + dr[i];
        int nextC = c + dc[i];

		if (nextR > 5 || nextC > 5 ||nextC < 0 || nextR < 0)	continue;
		if (Data[nextR][nextC] == d[0]) {
			retVal = Find(nextR, nextC, d.substr(1));
		}
	}

	return retVal;
}

void sol()
{
	string word;
	int nWord;
	cin >> nWord;
	while (nWord--)
	{
		int retVal = -1;
		word.clear();
		cin >> word;

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (Data[i][j] == word[0]) {
					retVal = Find(i, j, word.substr(1));
				}
				if (retVal == 1) break;
			}
			if (retVal == 1) break;
		}
		if (retVal == 1) cout << word << " yes" << endl;
		else            cout << word << " no" << endl;
	}
}

int main()
{
	int tc;
	cin >> tc;
	while (tc--) {
		input();
		sol();
	}
}