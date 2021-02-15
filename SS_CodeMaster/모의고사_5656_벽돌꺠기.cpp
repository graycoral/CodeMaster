#include<iostream>
#include<cstring>
#include<iomanip>

#define MIN(a,b) ((a) > (b) ? (b):(a))

using namespace std;

int dr[] = {1, -1, 0, 0};
int dc[] = { 0, 0 , 1, -1 };
int arr[13][16];
int visiited[13][16];
int c_arr[13][16];
int N, W, H;
int real_cnt = 0xffff;
int idx_arr[10];

int countMap()
{
	int retCnt = 0;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (c_arr[i][j] > 0) retCnt++;
		}
	}

	return retCnt;
}

void show_idx_arr()
{
	for (int i = 0; i < N; i++) {
		cout << idx_arr[i] << " ";
	}
	cout << ":" << countMap() << endl;
}

void input()
{
	for (int r = 0; r < H; r++) {
		for (int c = 0; c < H; c++) {
			cin >> arr[r][c];
			c_arr[r][c] = arr[r][c];
			visiited[r][c] = 0xffff;
		}
	}
}

void init_map()
{
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			c_arr[i][j] = arr[i][j];
		}
	}
}

int findR(int c)
{
	for (int i = 0; i < H; i++) {
		if (c_arr[i][c] > 0)	return i;
	}

	return -1;
}

void rebuild()
{
	int tmpArr[15] = { 0 };
	memset(tmpArr, 0, sizeof(tmpArr));

	for (int c = 0; c < W; c++) {
		int idx = 0;
		for (int r = 0; r < H; r++) {
			if (c_arr[r][c] > 0)	tmpArr[idx++] = c_arr[r][c];
		}
		for (int i = 0; i < H; i++) {
			c_arr[i][c] = tmpArr[idx - 1 -i];
			visiited[i][c] = 0;
		}
	}
}

void DFS(int r, int c)
{
	visiited[r][c] = 1;
	c_arr[r][c] = 0;

	for (int i = 0; i < 4; i++) {
		for (int j = 1; j <= arr[r][c]; j++) {
			int nr = r + (dr[i] * j);
			int nc = c + (dc[i] * j);

			if (nr < 0 || nc < 0 || nr >= H || nc >= W)	continue;
			if (visiited[nr][nc] == 1)	continue;

			DFS(nr, nc);
		}
	}
}

int breaBrick(int revC, int cnt)
{
	int retVal = 0xffff;
	int tmpArr[15][15] = { 0 };

	if (cnt > N) {
		show_idx_arr();
		return countMap();
	}
	idx_arr[cnt - 1] = revC;

	int r = findR(revC);
	if (r == -1)	return retVal;
	DFS(r, revC);
	rebuild();

	// copy
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			tmpArr[i][j] = c_arr[i][j];
		}
	}

	for (int c = 0; c < W; c++) {
		int tmpCnt = breaBrick(c, cnt + 1);
		retVal = MIN(tmpCnt, retVal);

		// init
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				c_arr[i][j] = tmpArr[i][j];
			}
		}
	}

	return retVal;
}

int breakBrick2(int c, int idx)
{
	int retVal = 0xffff;
	int tmpArr[15][15] = { 0 };

	if(idx > N){
		show_idx_arr();
		return countMap();
	}


	int r = findR(c);
	if (r == -1)	return retVal;
	c_arr[r][c] = 0;
	visiited[r][c] = 1;
	DFS(r, c);
	rebuild();

	// copy
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			tmpArr[i][j] = c_arr[i][j];
		}
	}

	for(int i = 0; i<W; i++) {
		idx_arr[idx] = i;
		int tmpCnt =  breakBrick2(i, idx+1);
		retVal = MIN(tmpCnt, retVal);

		// init
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				c_arr[i][j] = tmpArr[i][j];
			}
		}
	}
}

int sol()
{
	int retVal = 0xffff;

	for (int c = 0; c < W; c++) {
		init_map();
		idx_arr[0] = c;
		// int tmpCnt = breaBrick(c, 1);
		int tmpCnt = breakBrick2(c, 0);
		retVal = MIN(retVal, tmpCnt);
	}

	return retVal;
}

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int test_case;
	int T;

	freopen("5656_input.txt", "r", stdin);

	cin >> T;
	/*
	   ���� ���� �׽�Ʈ ���̽��� �־����Ƿ�, ������ ó���մϴ�.
	*/
	for (test_case = 1; test_case <= T; ++test_case)
	{
		cin >> N >> W >> H;
		input();
		sol();
		cout << "#" << test_case << " " << sol() << endl;

	}
	return 0;//��������� �ݵ�� 0�� �����ؾ��մϴ�.
}