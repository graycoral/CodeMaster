#if 1
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

	{{1, 0}, { 2,0 }, { 2, 1 }}, // type 2
	{{0, 1}, { 1,1 }, {2, 1}}, // type 2 
	{{0, 1}, { 0,2 }, {1, 2}}, // type 2
	{{1, 0}, { 1,1 }, {1, 2}}, // type 2
	{{1, 0}, { 0,1 }, {0, 2}}, // type 2
	{{0, 1}, { 0,2 }, {-1, 2}}, // type 2
	{{0, 1}, { 1,0 }, {2, 0}}, // type 2
	{{1, 0}, { 2,0 }, {2, -1}}, // type 2

	{{1, 0}, { 1,1 }, {2, 1}}, // type 3
	{{1, 0}, { 1,-1 }, { 2, -1 }}, // type 3
	{{0, 1}, { 1,1 }, {1, 2}}, // type 3
	{{0, 1}, { -1,1 }, {-1, 2}}, // type 3

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
	//freopen("BAEKJOON_14500_��Ʈ�ι̳�.txt", "r", stdin);
	int t = 1;
	//cin >> t;
	for (int i = 1; ; i++) {
		input();
		if (N == 0)	return 0;
		sol();
		cout <<i<<". " << ans << endl;
	}
	
	return 0;
}

#elif
#include <iostream>
#include <algorithm>
#include <vector>

#define MAX_NUM 200
#define DIR_NUM 4

using namespace std;

int n, m;
int grid[MAX_NUM][MAX_NUM];
int max_sum;

vector<pair<int, int> > visited_pos;

int dx[DIR_NUM] = {-1, 1, 0, 0};
int dy[DIR_NUM] = {0, 0, -1, 1};

// �־��� ��ġ�� ���ڸ� ������� ���θ� ��ȯ�մϴ�.
int InRange(int x, int y) {
	return x >= 0 && x < n && y >= 0 && y < m;
}

// �־��� ��ġ�� �̵��� �� �ִ��� ���θ� Ȯ���մϴ�.
int CanGo(int x, int y) {
	if(!InRange(x, y))
		return false;

	pair<int, int> pos = make_pair(x, y);
	for(int i = 0; i < (int) visited_pos.size(); i++)
		if(visited_pos[i] == pos)
			return false;

	return true;
}

// �־��� ��ġ�� ���Ͽ� ������ ��� ����� Ž���ϸ� �ִ� ���� ��ȯ�մϴ�.
void GetMaxSum(int cnt, int sum) {
	if(cnt == 4) {
		max_sum = max(max_sum, sum);
		return;
	}

	// ���ݱ��� �湮�� ��ġ���� Ž���ϸ鼭 ������ ��ġ�� �̵��� �� �ִ����� Ȯ���մϴ�.
	for(int i = 0; i < (int) visited_pos.size(); i++) {
		int x = visited_pos[i].first;
		int y = visited_pos[i].second;
		for(int dir = 0; dir < DIR_NUM; dir++) {
			int new_x = x + dx[dir];
			int new_y = y + dy[dir];

			if(CanGo(new_x, new_y)) {
				visited_pos.push_back(make_pair(new_x, new_y));
				GetMaxSum(cnt + 1, sum + grid[new_x][new_y]);
				visited_pos.pop_back();
			}
		}
	}

	return;
}

int main() {

	// �Է�:
	cin >> n >> m;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			cin >> grid[i][j];

	// ������ �� ��ġ�� ���Ͽ� Ž���Ͽ��ݴϴ�.
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			visited_pos.push_back(make_pair(i, j));
			GetMaxSum(1, grid[i][j]);
			visited_pos.pop_back();
		}
	}

	cout << max_sum;
}
#endif