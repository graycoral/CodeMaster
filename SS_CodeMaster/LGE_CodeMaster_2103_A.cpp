#include <iostream>

using namespace std;

typedef struct pos {
	int r, c;
} pos;

char map[3][10]{
	{'Q','W','E','R','T','Y','U','I','O','P'},
	{'A','S','D','F','G','H','J','K','J','L'},
	{'Z','X','C','V','B','N','M'}
};

int cnt = 0;
char input[100 + 1];

void init()
{
	for (int i = 0; i < sizeof(input); i++) {
		input[i] = -1;
	}
	cin >> input;
	cnt = 1;
}

pos GetPos(char ch)
{
	pos ret = {0,0};

	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 10; c++) {
			if (map[r][c] == ch) {
				ret.r = r; ret.c = c;
				return ret;
			}
		}
	}

	return ret;
}

void countKey()
{
	int curIdx = 0;

	while (input[curIdx+1] != 0) {
		pos cur = GetPos(input[curIdx]);
		pos next = GetPos(input[curIdx + 1]);
		pos newPos = { 0,0 };

		while (!(newPos.r == next.r && newPos.c == next.c)) {
			if (cur.r < next.r) {
				newPos.r = cur.r + 1;
			}
			else if (cur.r == next.r) {
				newPos.r = cur.r;
			}
			else if (cur.r > next.r) {
				newPos.r = cur.r - 1;
			}

			if (cur.c < next.c) {
				newPos.c = cur.c + 1;
			}
			else if (cur.c == next.c) {
				newPos.c = cur.c;
			}
			else if (cur.c > next.c) {
				newPos.c = cur.c - 1;
			}

			cnt += 2;
			if (newPos.r == next.r && newPos.c == next.c) {
				curIdx += 1;
				cnt += 1;
			}
			else {
				cur.r = newPos.r; cur.c = newPos.c;
			}
		}
	}
}


int main()
{
	int T;
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	freopen("LGE_CodeMaster_2103_A.txt", "r", stdin);
	cin >> T;

	for (int i = 0; i < T; i++) {
		init();
		countKey();
		cout << cnt << endl;
	}

	return 0;
}