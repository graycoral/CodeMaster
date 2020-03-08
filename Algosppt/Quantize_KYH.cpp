#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int N, S;
vector<int> num;
int cache[101][11];
int pSum[101];
int pSqSum[101];
const int INF = 987654321;

int minError(int lo, int hi)
{
	int sum = pSum[hi] - (lo == 0 ? 0 : pSum[lo - 1]);
	int sqSum = pSqSum[hi] - (lo == 0 ? 0 : pSqSum[lo - 1]);

	int m = int(0.5 + ((double)sum / (hi - lo + 1)));
	//¢²(arr[i]-mean)^2 = (high-low+1)*mean^2 - 2*(¢²arr[i])*mean + ¢²arr[i]^2
	int ret = sqSum - 2 * m * sum + m * m * (hi - lo + 1);

	return ret;
}

int quantize(int from, int parts)
{
	if (from == N)	return 0;
	if (parts == 0) return INF;

	int& ret = cache[from][parts];
	if (ret != -1)	return ret;

	ret = INF;
	for (int partSize = 1; partSize + from <= N; partSize++) {
		ret = min(ret, minError(from, from + partSize - 1) + quantize(from + partSize, parts - 1));
	}

	return ret;
}

void clear()
{
	num.clear();
	memset(cache, -1, sizeof(cache));
	memset(pSqSum, 0, sizeof(pSqSum));
	memset(pSum, 0, sizeof(pSum));
}

void precalc()
{
	sort(num.begin(), num.end());
	pSum[0] = num[0];
	pSqSum[0] = num[0] * num[0];

	for (int i = 1; i < N; ++i) {
		pSum[i] = pSum[i - 1] + num[i];
		pSqSum[i] = pSqSum[i - 1] + num[i] * num[i];
	}
}

int main()
{
	int tc;

	cin >> tc;
	while (tc--) {
		clear();
		cin >> N >> S;
		int tmp;
		for (int i = 0; i < N; i++) {
			cin >> tmp;
			num.push_back(tmp);
		}
		precalc();
		cout << quantize(0, S) << endl;
	}
	return 0;
}