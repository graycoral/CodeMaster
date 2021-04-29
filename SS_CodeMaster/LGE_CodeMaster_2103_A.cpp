#include <iostream>
#define MAX(a,b) ((a)> (b) ? (a) : (b))
using namespace std;

typedef struct pos {
	int r, c;
} pos;

char map[3][10]{
	{'Q','W','E','R','T','Y','U','I','O','P'},
	{'A','S','D','F','G','H','J','K','L'},
	{'Z','X','C','V','B','N','M'}
};

int cnt = 0;
char input[100 + 1];

pos keyPos[100 + 1];

void init()
{
	for (int i = 0; i < sizeof(input); i++) {
		input[i] = -1;
	}
	cin >> input;
	cnt = 1;
}

void makeKeyPos()
{
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 10; c++) {
			keyPos[map[r][c]].r = r;
			keyPos[map[r][c]].c = c;
		}
	}
}

pos GetPos(char ch)
{
	return keyPos[ch];
}

void countKey()
{
	int curIdx = 0;	

	while (input[curIdx + 1] != 0) {
		pos cur = GetPos(input[curIdx]);
		pos next = GetPos(input[curIdx +1]);
		int dist = 0;
		int distR = cur.r - next.r;		
		int distC = cur.c - next.c;
		
		if ((distR ^ distC) >= 0)	dist = (distR > 0 ? distR : distR * -1) + (distC > 0 ? distC : distC * -1);
		else dist = MAX(distC > 0 ? distC : distC * -1, distR > 0 ? distR : distR * -1);

		cnt += (dist * 2 + 1) ;
		curIdx++;
	}

	cout << cnt << endl;
}


int main()
{
	int T;
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	//freopen("LGE_CodeMaster_2103_A.txt", "r", stdin);
	cin >> T;

	makeKeyPos();
	for (int i = 0; i < T; i++) {
		init();
		countKey();
	}

	return 0;
}


#if 0
#include <bits/stdc++.h>

using namespace std;

vector<string> keys = {
	"QWERTYUIOP",
	"ASDFGHJKL",
	"ZXCVBNM" };

map<char, pair<int, int>> key_pos;

void solve(int c)
{
	string s;
	cin >> s;

	int result = s.size();

	char cur = s[0];
	pair<int, int> cur_p = key_pos[cur];

	for (int i = 1; i < s.size(); ++i)
	{
		char next = s[i];
		pair<int, int> next_p = key_pos[next];

		int diff_r = next_p.first - cur_p.first;
		int diff_c = next_p.second - cur_p.second;

		result += max(abs(diff_r + diff_c), max(abs(diff_r), abs(diff_c))) * 2;

		cur_p = next_p;
	}

	cout << result << endl;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	for (int i = 0; i < keys.size(); ++i)
	{
		string line = keys[i];
		for (int j = 0; j < line.size(); ++j)
		{
			char key = line[j];
			key_pos[key] = make_pair(i, j);
		}
	}

	int t;
	cin >> t;
	for (int i = 0; i < t; ++i)
	{
		solve(t);
	}

	return 0;
}

#endif