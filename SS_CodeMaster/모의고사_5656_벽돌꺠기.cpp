#include<iostream>
#include<cstring>
#include<iomanip>

#define MIN(a,b) ((a) > (b) ? (b):(a))

using namespace std;

int dc[] = {1, -1, 0, 0};
int dr[] = { 0, 0 , 1, -1 };
int arr[16][16];
int visited[16][16];
int c_arr[16][16];
int N, W, H;
int idx_arr[256];
int minCnt = 0xffff;

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
	minCnt = 0xffff;
	cin >> N >> W >> H;
	for (int r = 0; r < H; r++) {
		for (int c = 0; c < W; c++) {
			cin >> arr[r][c];
			c_arr[r][c] = arr[r][c];
			visited[r][c] = 0xffff;
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

	for (int c = 0; c < W; c++) {
		int idx = 0;
		memset(tmpArr, 0, sizeof(tmpArr));
		for (int r = 0; r < H; r++) {
			if (c_arr[r][c] > 0)	tmpArr[idx++] = c_arr[r][c];
		}
		if (idx == 0)	continue;
		idx -= 1;

		for (int i = H - 1; i >= 0; i--) {
			if (idx < 0) c_arr[i][c] = 0;
			else c_arr[i][c] = tmpArr[idx--];
			visited[i][c] = 0;
		}
		
	}
}

void DFS(int r, int c)
{	
	int idx = c_arr[r][c] - 1;
	visited[r][c] = 1;
	for (int i = 0; i < 4; i++) {
		for (int j = 1; j <= idx; j++) {
			int nr = r + (dr[i] * j);
			int nc = c + (dc[i] * j);

			if (nr < 0 || nc < 0 || nr >= H || nc >= W)	continue;
			if (visited[nr][nc] == 1)	continue;
			if (c_arr[nr][nc] == 0) continue;

			DFS(nr, nc);			
		}		
	}
	c_arr[r][c] = 0;
	visited[r][c] = 0;
}

void breakBrick2(int idx)
{
	/*if (countMap() == 0) {
		minCnt = 0;
		return;
	}*/
	
	if (minCnt == 0)	return;
	if (idx >= N)	return;	
	
	// copy
	int tmpArr[16][16] = { 0 };
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			tmpArr[i][j] = c_arr[i][j];
		}
	}

	for(int i = 0; i<W; i++) {
		int tmpCnt = 0xffff;
		int r = findR(i);
		if (r == -1)	continue;

		idx_arr[idx] = i;
		DFS(r, i);
		rebuild();
		breakBrick2(idx+1);		

		tmpCnt = countMap();
		minCnt = MIN(tmpCnt, minCnt);

		// init
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				c_arr[i][j] = tmpArr[i][j];

			}
		}
	}
}

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int test_case;
	int T;

	freopen("5656_input.txt", "r", stdin);

	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{		
		input();
		if (countMap()) breakBrick2(0);
		else minCnt = 0;

		cout << "#" << test_case << " " << minCnt << endl;

	}
	return 0;
}