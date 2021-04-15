#include <iostream>
#include <cstring>
using namespace std;

const int maxn = 500 + 10;
int map[maxn][maxn];

typedef struct pos {
	int r, c;
}Pos;


Pos d[][3] = {
	{{0, 1}, { 0,2 }, { 0,3 }}, // type 1
	{{1, 0}, { 2,0 }, { 3,0 }}, // type 1

	//{{1, 0}, { 2,0 }, { 2, 1 }}, // type 2
	//{{0, 1}, { 1,1 }, {2, 1}}, // type 2 
	{{0, 1}, { 0,2 }, {1, 2}}, // type 2
	{{1, 0}, { 1,1 }, {1, 2}}, // type 2
	//{{1, 0}, { 0,1 }, {0, 2}}, // type 2
	//{{0, 1}, { 0,2 }, {-1, 2}}, // type 2
	{{0, 1}, { 1,0 }, {2, 0}}, // type 2
	{{1, 0}, { 2,0 }, {2, -1}}, // type 2

	//{{1, 0}, { 1,1 }, {2, 1}}, // type 3
	{{1, 0}, { 1,-1 }, { 2, -1 }}, // type 3
	{{0, 1}, { 1,1 }, {1, 2}}, // type 3
	//{{0, 1}, { -1,1 }, {-1, 2}}, // type 3

	{{0, 1}, { 0, 2 }, {-1, 1}}, // type 4
	{{0, 1}, { 0, 2 }, {1, 1}}, // type 4
	{{1, 0}, { 2, 0 }, { 1, 1 }}, // type 4
	{{1, 0}, { 2, 0 }, {1, -1}}, // type 4

	{{1, 1}, { 0, 1 }, {1, 0}} // type 5				
};

int N, M;
int ans = 0;

void input()
{
	cin >> N;
	memset(map, 0xfffe, sizeof(map));
	ans = -987654321;
	if (N == 0)	return;
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			cin >> map[r][c];
		}
	}
}

void sol()
{
	int tmpSum = 0;
	int setFlag = 1;
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			for (int i = 0; i < 13; i++) {
				tmpSum = map[r][c];
				for (int j = 0; j < 3; j++) {
					if (map[r + d[i][j].r][c + d[i][j].c] == 0xfffe) {
						setFlag = 0;
						break;
					}
					tmpSum += map[r + d[i][j].r][c + d[i][j].c];
				}
				if (ans < tmpSum && setFlag == 1)	ans = tmpSum;
				setFlag = 1;
			}

		}
	}
}
int main()
{
	//freopen("BAEKJOON_14500_테트로미노.txt", "r", stdin);
	int t = 1;
	//cin >> t;
	for (int i = 1; ; i++) {
		input();
		if (N == 0)	return 0;
		sol();
		cout << i << ". " << ans << endl;
	}

	return 0;
}