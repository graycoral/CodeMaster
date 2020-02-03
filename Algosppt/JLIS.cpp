#include <iostream>
#include <algorithm>
#include <cstring>
#include <climits>

using namespace std;

const int MAXN = (1e2 + 1);

int cache[MAXN][MAXN];
int A[MAXN], B[MAXN];
int tc, n, m;

int jlis(int idxA, int idxB)
{
	int& ret = cache[idxA+1][idxB+1];

	if (ret != -1)   return ret;

	long long a = (idxA == -1 ? INT_MIN : A[idxA]);
	long long b = (idxB == -1 ? INT_MIN : B[idxB]);

	int maxElement = max(a, b);
	ret = 0;

	for (int i = idxA + 1; i < n; i++) {
		if (maxElement < A[i]) {
			ret = max(ret, jlis(i, idxB) + 1);
		}
	}
	for (int i = idxB + 1; i< m; i++) {
		if (maxElement < B[i]) {
			ret = max(ret, jlis(idxA, i) + 1);
		}
	}
	return ret;
}

int main()
{
	cin >> tc;

	while (tc--) {
		cin >> n >> m;
		memset(A, 0, sizeof(A));
		memset(B, 0, sizeof(B));
		memset(cache, -1, sizeof(cache));
		for (int i = 0; i < n; i++) {
			cin >> A[i];
		}
		for (int i = 0; i < m; i++) {
			cin >> B[i];
		}
		cout << jlis(-1, -1) << endl;
	}

	return 0;
}