#include <iostream>
#include <tuple>
#include <queue>
#include <cassert>
#include <iomanip>

#define MAX_N 20
#define DIR_NUM 4
#define RED 0
#define ROCK -1
#define EMPTY -2
#define EMPTY_BUNDLE make_tuple(-1, -1, -1, -1)

using namespace std;

typedef tuple<int, int, int, int> Bundle;

int n, m;

int grid[MAX_N][MAX_N];
int temp[MAX_N][MAX_N];

queue<pair<int, int> > bfs_q;
bool visited[MAX_N][MAX_N];

int ans;

#define DEBUG (1)

void show(string str)
{
#if DEBUG
	cout << "=============" << str << " : " << ans << "=======================" << endl;
	for (int r = 0; r < n; r++) {
		for (int c = 0; c < n; c++) {
			cout << setw(3) << grid[r][c];
		}
		cout << endl;
	}
	cout << "==========================================================" << endl;
#endif
}


bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

// 같은 색이거나, 빨간색 폭탄인 경우에만 이동이 가능합니다.
bool CanGo(int x, int y, int color) {
	return InRange(x, y) && !visited[x][y] && (
		grid[x][y] == color || grid[x][y] == RED
		);
}

void BFS(int x, int y, int color) {
	// visited 값을 초기화합니다.
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			visited[i][j] = false;

	// 시작점을 표시합니다.
	visited[x][y] = true;
	bfs_q.push(make_pair(x, y));

	int dx[DIR_NUM] = { 0, 1, 0, -1 };
	int dy[DIR_NUM] = { 1, 0, -1, 0 };

	// BFS 탐색을 수행합니다.
	while (!bfs_q.empty()) {
		pair<int, int> curr_pos = bfs_q.front();
		int curr_x, curr_y;
		tie(curr_x, curr_y) = curr_pos;
		bfs_q.pop();

		for (int i = 0; i < DIR_NUM; i++) {
			int new_x = curr_x + dx[i];
			int new_y = curr_y + dy[i];

			if (CanGo(new_x, new_y, color)) {
				bfs_q.push(make_pair(new_x, new_y));
				visited[new_x][new_y] = true;
			}
		}
	}
}

// (x, y) 지점을 시작으로 bundle 정보를 계산해 반환합니다.
Bundle GetBundle(int x, int y) {
	// Step1. (x, y)를 시작으로 bfs 탐색을 진행합니다.
	BFS(x, y, grid[x][y]);

	// Step2. bundle 정보를 계산해 반환합니다.
	int bomb_cnt = 0, red_cnt = 0;
	pair<int, int> standard = make_pair(-1, -1);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			if (!visited[i][j])
				continue;

			bomb_cnt++;

			if (grid[i][j] == RED)
				red_cnt++;
			else if (make_pair(i, -j) > standard)
				standard = make_pair(i, -j);
		}

	int std_x, std_y;
	tie(std_x, std_y) = standard;
	return make_tuple(bomb_cnt, -red_cnt, std_x, std_y);
}

// 우선순위에 따라 쉽게 계산하기 위해
// (폭탄 묶음의 크기, -빨간색 폭탄의 수, 행 번호, -열 번호)
// 순서대로 값을 넣어줍니다.
Bundle FindBestBundle() {
	Bundle best_bundle = EMPTY_BUNDLE;

	// 빨간색이 아닌 폭탄들에 대해서만 전부 탐색합니다.
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (grid[i][j] >= 1) {
				Bundle bundle = GetBundle(i, j);
				if (bundle > best_bundle)
					best_bundle = bundle;
			}
	show("FindBestBundle");
	return best_bundle;
}

void Remove(int col) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (visited[i][j]) {
				assert(grid[i][j] == col || grid[i][j] == RED);
				grid[i][j] = EMPTY;
			}

	show("remove");
}

void Gravity() {
	// Step1.
	// 중력 작용을 쉽게 구현하기 위해
	// temp 배열을 활용합니다.
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			temp[i][j] = EMPTY;

	// Step2.
	for (int j = 0; j < n; j++) {
		// 아래에서 위로 올라오면서
		// 해당 위치에 폭탄이 있는 경우에만 temp에 
		// 쌓아주는 식으로 코드를 작성할 수 있습니다.

		// 단, 돌이 있는 경우에는
		// 위에부터 쌓일 수 있도록 합니다.
		int last_idx = n - 1;
		for (int i = n - 1; i >= 0; i--) {
			if (grid[i][j] == EMPTY)
				continue;
			if (grid[i][j] == ROCK)
				last_idx = i;
			temp[last_idx--][j] = grid[i][j];

		}
	}

	// Step3. 다시 temp 배열을 옮겨줍니다.
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			grid[i][j] = temp[i][j];
	
	show("gravity");
}

// 반시계 방향으로 90' 만큼 회전합니다.
void Rotate() {
	// Step1. 
	// 회전 과정을 쉽게 구현하기 위해
	// temp 배열을 활용합니다.
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			temp[i][j] = EMPTY;

	// Step2.
	// 기존 격자를 반시계 방향으로 90도 회전했을 때의 결과를
	// temp에 저장해줍니다.
	for (int j = n - 1; j >= 0; j--)
		for (int i = 0; i < n; i++)
			temp[n - 1 - j][i] = grid[i][j];

	// Step3.
	// 다시 temp 배열을 옮겨줍니다.
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			grid[i][j] = temp[i][j];

	show("reorder");
}

void Clean(int x, int y) {
	// Step1. (x, y)를 시작으로 지워야할 폭탄 묶음을 표시합니다.
	BFS(x, y, grid[x][y]);

	// Step2. 폭탄들을 전부 지워줍니다.
	Remove(grid[x][y]);

	// Step3. 중력이 작용합니다.
	Gravity();
}

bool Simulate() {
	// Step1. 크기가 최대인 폭탄 묶음을 찾습니다.
	Bundle best_bundle = FindBestBundle();

	int bomb_cnt, x, y;
	tie(bomb_cnt, ignore, x, y) = best_bundle;

	// 만약 폭탄 묶음이 없다면, 종료합니다.
	if (best_bundle == EMPTY_BUNDLE || bomb_cnt <= 1)
		return false;

	// Step2. 선택된 폭탄 묶음에 해당하는 폭탄들을 전부 제거 후
	//        중력이 작용합니다.
	ans += bomb_cnt * bomb_cnt;
	Clean(x, -y);

	// Step3. 반시계 방향으로 90' 만큼 회전합니다.
	Rotate();

	// Step4. 중력이 작용합니다.
	Gravity();	
	return true;
}

int main() {
	int test_case = 1;

	freopen("색깔폭탄.txt", "r", stdin);
	cin >> test_case;
	cin >> n >> m;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> grid[i][j];

	// 끝나기 전까지 시뮬레이션을 반복합니다.
	while (true) {
		bool keep_going = Simulate();

		if (!keep_going)
			break;
	}

	cout << ans;
}