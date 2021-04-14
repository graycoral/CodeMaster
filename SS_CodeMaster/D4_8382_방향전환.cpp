#include <iostream>
#include <cstdlib>
using namespace std;

int sR, sC;
int eR, eC;

int dr1[] = {1, -1};
int dc1[] = {0, 0};
int dr2[] = {0, 0};
int dc2[] = {1, -1};

int ansCnt = 0xfffe;

void input()
{
	ansCnt = 0xfffe;
	cin >> sR >> sC >> eR >> eC;
}

void move(int r, int c, int d, int cnt)
{
	if (r > 200 || r < -200 || c> 200 || c < -200)	return;
	if (cnt >= ansCnt)	return;
	if (r == eR && c == eC) {
		if (ansCnt > cnt)	ansCnt = cnt;
		return;
	}
	int dist = 0xfffe;
	int nr = 0, nc = 0;
	if (d == 1) {
		for (int i = 0; i < 2; i++) {
			int tmpdistance = abs(eR - r - dr2[i]) + abs(eC - c - dc2[i]);
			if (dist > tmpdistance) {
				dist = tmpdistance;
				if (dist < 0)	dist *= -1;
				nr = r + dr2[i];
				nc = c + dc2[i];
			}
		}
		move(nr, nc, 0, cnt + 1);
	}
	else {
		for (int i = 0; i < 2; i++) {
			int tmpdistance = abs(eR - r - dr1[i]) + abs(eC - c - dc1[i]);
			if (dist > tmpdistance) {
				dist = tmpdistance;
				if (dist < 0)	dist *= -1;
				nr = r + dr1[i];
				nc = c + dc1[i];
			}			
		}
		move(nr, nc, 1, cnt + 1);
	}
}

void sol()
{
	move(sR, sC, 1, 0);
	move(sR, sC, 0, 0);
}

int main()
{
	int test_case = 1;
	freopen("D4_8382_방향전환.txt", "r", stdin);
	cin >> test_case;

	for (int i = 1; i <= test_case; i++) {
		input();
		sol();
		cout << "#" << i << " " << ansCnt << endl;
	}
	return 0;
}