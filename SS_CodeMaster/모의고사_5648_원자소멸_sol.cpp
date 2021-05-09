#include <iostream>

using namespace std;

int atom[1000][4];
int visit[4005][4005];
bool collided[4005][4005];

void RemoveAtom(int n, int* pnsize)
{
	int nLastIndex = (*pnsize) - 1;
	atom[n][0] = atom[nLastIndex][0];
	atom[n][1] = atom[nLastIndex][1];
	atom[n][2] = atom[nLastIndex][2];
	atom[n][3] = atom[nLastIndex][3];
	(*pnsize)--;
}

int sol(int N)
{
	int nReset = N;
	int ans = 0;

	for (int j = 0; j < nReset; ++j) {
		atom[j][0] = atom[j][0] * 2;
		atom[j][1] = atom[j][1] * 2;

		visit[atom[j][0]][atom[j][1]]++;
	}

	int nMaxLoop = 4002;
	for (int i = 0; i < nMaxLoop; ++i) {
		for (int j = 0; j < nReset; ++j) {
			int& x = atom[j][0];
			int& y = atom[j][1];
			int d = atom[j][2];

			visit[x][y]--;

			if (d == 0)	y++;
			else if (d == 1)	y--;
			else if (d == 2)	x++;
			else if (d == 3)	x--;

			if (atom[j][0] < 0 || atom[j][0] > 4000 || \
				atom[j][1] < 0 || atom[j][1] > 4000) {
				RemoveAtom(j, &nReset);
				j--;
			}
			else {
				visit[x][y]++;
				if (visit[x][y] >= 2)	collided[x][y] = true;
			}
		}

		for (int j = 0; j < nReset; j++) {
			int x = atom[j][0]; int y = atom[j][1];
			if (collided[x][y] == true) {
				if (visit[x][y] == 1)	collided[x][y] = false;
				visit[x][y]--;
				ans += atom[y][3];
				RemoveAtom(j, &nReset);
				j--;
			}
		}

		if (nReset == 0)	break;
	}

	return ans;
}

int main()
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	//freopen("���ǰ���_5648_���ڼҸ�.txt", "r", stdin);

	int T, test_case = 0;
	int i;

	for (test_case = 1; test_case <= T; test_case++)
	{
		int N = 0;
		cin >> N;
		for (int i = 0; i < N; i++) {
			cin >> atom[i][0] >> atom[i][1] >> atom[i][2] >> atom[i][3];
			atom[i][0] += 1000;
			atom[i][1] += 1000;
		}
		int nRes = sol(N);
		cout << "#" << test_case << " " << nRes << endl;
	}
}