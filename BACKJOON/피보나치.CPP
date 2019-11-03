#include <iostream>
#include <cstring>

using namespace std;

int cache[41] = { 0, };

int main()
{
	int n, tmp, cnt, cnt1;
	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> tmp;
		cache[tmp] = 1;
		for (int j = tmp; j > 1; j--) {
			cache[j - 1] += cache[j];
			cache[j - 2] += cache[j];
		}

		cout << cache[0] << " " << cache[1] << endl;
		memset(cache, 0, sizeof(cache));
	}

	return 0;
}