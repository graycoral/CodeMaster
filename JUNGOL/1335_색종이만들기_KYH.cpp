#include <iostream>
#include <map>
#include <vector>

using namespace std;
constexpr int max_n = 256;
int N;
int Map[max_n][max_n];
int v[max_n][max_n];
int blue, white;

void input()
{
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> Map[i][j];
		}
	}
}

void sol(int r, int c, int len)
{
	if (r > N || c > N)	return;
	if (len == 0)	return;
	if (v[r][c] != 0)	return;

	int dr[] = { 0, len / 2, 0, len / 2 };
	int dc[] = { 0, len / 2, len / 2, 0 };
	int check = 1;
	int start = Map[r][c];

	for (int i = r; i < r + len; i++) {
		for (int j = c; j < c + len; j++) {
			if (Map[i][j] != start) {
				check = -1;	break;
			}
		}
		if (check == -1) break;
	}

	if (check == 1) {
		if (start == 1) blue++;
		else           white++;

		for (int i = r; i < r + len; i++) {
			for (int j = c; j < c + len; j++) {
				if (start == 1) v[i][j] = blue;
				else           v[i][j] = -white;
			}
		}
	}
	else {
		for (int i = 0; i < 4; i++) {
			sol(r + dr[i], c + dc[i], len / 2);
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	input();
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			sol(i, j, N);
		}
	}

	cout << white << endl;
	cout << blue << endl;

	return 0;
}