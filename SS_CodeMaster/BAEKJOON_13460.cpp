#include <iostream>

using namespace std;

const int maxn = 10 + 1;
int N, M;

int dr[] = { 1, -1, 0, 0 };
int dc[] = { 0, 0, 1, -1 };

char map[maxn + 1][maxn + 1];
int findFlag = 0;
int cnt = 0xfffe;

typedef struct pos {
	int r, c;
} pos;

pos R;
pos B;

void input()
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			char tmp;
			cin >> tmp;
			map[i][j] = tmp;
			if (tmp == 'R') {
				R.r = i; R.c = j;
			}
			if (tmp == 'B') {
				B.r = i; B.c = j;
			}
		}
	}	
	findFlag = 0;
	cnt = 0xfffe;
}

void show(int cnt)
{
	cout << "============"<< cnt << "============" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << map[i][j] << " ";			
		}
		cout << endl;
	}
	cout << "============" << endl;
}

pos findNewPos(pos cur, int dic, char col)
{	
	pos pre = cur;
	while (1) {
		cur.r += dr[dic];
		cur.c += dc[dic];

		if ((map[cur.r][cur.c] == '#' || \
			map[cur.r][cur.c] == 'R' || \
			map[cur.r][cur.c] == 'B')) {
			cur.r -= dr[dic];
			cur.c -= dc[dic];
			break;
		}
		else if (map[cur.r][cur.c] == 'O') {
			cur.r = maxn; cur.c = maxn;
			findFlag = 1;			
			break;
		}
	}

	if (cur.r != maxn) {
		map[pre.r][pre.c] = '.';
		map[cur.r][cur.c] = col;
	}
	else {
		map[pre.r][pre.c] = '.';
	}
	
	return cur;
}

void DFS(pos red, pos blue, int preDir, int ballCnt)
{	
	if (ballCnt > 10)	return;
	if (ballCnt > cnt && cnt != -1)	return;
	//show(ballCnt);

	preDir = preDir % 2 ? preDir - 1 : preDir + 1;
	for (int i = 0; i < 4; i++) {
		int dfsFlag = 1;
		int dir = i;
		//if (findFlag)	return;
		if (preDir == dir) continue;
		//if (map[red.r + dr[dir]][red.c + dc[dir]] == '#') continue;
		if (!(map[red.r + dr[dir]][red.c + dc[dir]] == '.' || (map[red.r + dr[dir]][red.c + dc[dir]] == 'O')) && \
			!(map[blue.r + dr[dir]][blue.c + dc[dir]] == '.') )continue;

		pos nRed;
		pos nBlue;

		if ((dir == 0 && red.r > blue.r) || (dir == 1 && red.r < blue.r)) {
			nRed = findNewPos(red, dir, 'R');
			nBlue = findNewPos(blue, dir, 'B');
		}
		else if ((dir == 0 && red.r < blue.r) || (dir == 1 && red.r > blue.r)) {
			nBlue = findNewPos(blue, dir, 'B');
			nRed = findNewPos(red, dir, 'R');
		}
		else if ((dir == 2 && red.c < blue.c) || (dir == 3 && red.c > blue.c)) {
			nBlue = findNewPos(blue, dir, 'B');
			nRed = findNewPos(red, dir, 'R');			
		}
		else if ((dir == 2 && red.c > blue.c) || (dir == 3 && red.c < blue.c)) {		
			nRed = findNewPos(red, dir, 'R');
			nBlue = findNewPos(blue, dir, 'B');
		}
		else {
			nBlue = findNewPos(blue, dir, 'B');
			nRed = findNewPos(red, dir, 'R');			
		}

		if (nRed.r == maxn && nBlue.r == maxn) {
			dfsFlag = 0;
			if (cnt == 0xfffe) cnt = -1;
		}
		else if (nBlue.r == maxn) {
			dfsFlag = 0;
		}		
		else if (nRed.r == maxn) {
			dfsFlag = 0;
			if (cnt != -1) cnt = cnt > ballCnt ? ballCnt : cnt;
			else cnt = ballCnt;
		}

		if (dfsFlag) {
			DFS(nRed, nBlue, dir, ballCnt + 1);
		}

		if (nRed.r == maxn && nBlue.r == maxn) {
			map[red.r][red.c] = 'R';
			map[blue.r][blue.c] = 'B';
		}
		else {
			if (red.r == nRed.r && red.c == nRed.c) {
				map[red.r][red.c] = 'R';
			}
			else {
				map[red.r][red.c] = 'R';
				map[nRed.r][nRed.c] = '.';
			}

			if (blue.r == nBlue.r && blue.c == nBlue.c) {
				map[blue.r][blue.c] = 'B';
			}
			else {
				map[blue.r][blue.c] = 'B';
				map[nBlue.r][nBlue.c] = '.';
			}
		}		
	}
}

int main()
{
	int T = 1;
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);
	
	/*freopen("BAEKJOON_13460.txt", "r", stdin);
	cin >> T;*/
	

	for (int i = 0; i < T; i++) {
		cin >> N >> M;
		input();
		DFS(R, B, -1, 1);
		cnt = cnt > 10 ? -1 : cnt;
		cout << cnt << endl;
	}	

	return 0;
}