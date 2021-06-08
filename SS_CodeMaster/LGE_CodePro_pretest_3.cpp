#include <iostream>
#include <algorithm>

using namespace std;
#define MIN(a, b) ( a> b ? b : a)
int emptywall[2];
int order[20 + 1];
int N;
int ans = 987654321;

int sol()
{
	int cnt = 0;

	for (int i = 0; i < N - 2; i++) {
		if (abs(emptywall[0] - order[i]) <= abs(emptywall[1] - order[i])) {
			cnt += (emptywall[0] - order[i] < 0 ? (emptywall[0] - order[i]) * -1 : emptywall[0] - order[i]);
			emptywall[0] = order[i];
		}
		else {
			cnt += (emptywall[1] - order[i] < 0 ? (emptywall[1] - order[i]) * -1 : emptywall[1] - order[i]);
			emptywall[1] = order[i];
		}
	}

	return cnt;
}


void Move(int idx, int cnt)
{
	if (idx >= N) {
		ans = MIN(ans, cnt);
		return;
	}
	int tmpWall[2];
	for (int i = 0; i < 2; i++) {
		tmpWall[i] = emptywall[i];
	}
	
	emptywall[0] = order[idx];
	Move(idx+1, cnt + abs(emptywall[0] - order[idx]));

	for (int i = 0; i < 2; i++) {
		emptywall[i] = tmpWall[i];
	}

	emptywall[1] = order[idx];
	Move(idx + 1, cnt + abs(emptywall[1] - order[idx]));

	for (int i = 0; i < 2; i++) {
		emptywall[i] = tmpWall[i];
	}
}

int main()
{	
	cin >> N;
	for (int i = 0; i < 2; i++) {
		cin >> emptywall[i];
	}
	for (int i = 0; i < N - 2; i++) {
		cin >> order[i];
	}
	
	//cout << sol() << endl;
	Move(0, 0);
	cout << ans << endl;

	return 0;
}