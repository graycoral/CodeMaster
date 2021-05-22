#include <iostream>
#include <cstring>

using namespace std;

const int mod = 1000000007;

int N;
int cache[101];

int tiling(int width)
{
	if (width <= 1)	return 1;

	int& ret = cache[width];
	
	if (ret != -1)	return ret;
	return ret = (tiling(width - 2) + tiling(width - 1)) % mod;
}

int main()
{
	int T;
	cin >> T;

	for (int i = 0; i < T; i++) {
		int width = 0;
		cin >> width;
		memset(cache, -1, sizeof(cache));
		cout << tiling(width) << endl;
	}

	return 0;
}

