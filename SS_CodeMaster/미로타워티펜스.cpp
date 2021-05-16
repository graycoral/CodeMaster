#include <iostream>
#include <vector>
#include <tuple>

#define MAX_N 25
#define DIR_NUM 4

using namespace std;

int n, m;

int grid[MAX_N][MAX_N];
int temp[MAX_N][MAX_N];

vector<pair<int, int> > spiral_points;

int ans;

void SearchSpiral() {
	// 나선이 돌아가는 순서대로 
	// 왼쪽 아래 오른쪽 위 방향이 되도록 정의합니다.
	int dx[DIR_NUM] = { 0, 1, 0, -1 };
	int dy[DIR_NUM] = { -1, 0, 1, 0 };

	// 시작 위치와 방향, 
	// 해당 방향으로 이동할 횟수를 설정합니다. 
	int curr_x = n / 2, curr_y = n / 2;
	int move_dir = 0, move_num = 1;

	while (curr_x || curr_y) {
		// move_num 만큼 이동합니다.
		for (int i = 0; i < move_num; i++) {
			curr_x += dx[move_dir]; curr_y += dy[move_dir];
			spiral_points.push_back(make_pair(curr_x, curr_y));

			// 이동하는 도중 (0, 0)으로 오게 되면,
			// 움직이는 것을 종료합니다.
			if (!curr_x && !curr_y)
				break;
		}

		// 방향을 바꿉니다.
		move_dir = (move_dir + 1) % 4;
		// 만약 현재 방향이 왼쪽 혹은 오른쪽이 된 경우에는
		// 특정 방향으로 움직여야 할 횟수를 1 증가시킵니다.
		if (move_dir == 0 || move_dir == 2)
			move_num++;
	}
}

void Pull() {
	// Step 1. temp 배열을 초기화합니다.
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			temp[i][j] = 0;

	// Step2. 나선 순서대로 보며
	//        비어있지 않은 값들을 temp에 채워줍니다.
	int temp_idx = 0;
	for (pair<int, int> grid_point : spiral_points) {
		int gx, gy;
		tie(gx, gy) = grid_point;

		if (grid[gx][gy]) {
			int tx, ty;
			tie(tx, ty) = spiral_points[temp_idx];
			temp[tx][ty] = grid[gx][gy];
			temp_idx++;
		}
	}

	// Step 3. temp 값을 다시 grid에 옮겨줍니다.
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			grid[i][j] = temp[i][j];
}

void Attack(int d, int p) {
	// 문제에서 주어진 순서대로 → ↓ ← ↑
	int dx[DIR_NUM] = { 0, 1,  0, -1 };
	int dy[DIR_NUM] = { 1, 0, -1,  0 };

	// Step 1. d 방향으로 p마리의 몬스터를 제거합니다.
	int center_x = n / 2, center_y = n / 2;
	for (int dist = 1; dist <= p; dist++) {
		int nx = center_x + dx[d] * dist;
		int ny = center_y + dy[d] * dist;

		ans += grid[nx][ny];
		grid[nx][ny] = 0;
	}

	// Step2. 비어 있는 자리를 당겨서 채워줍니다.
	Pull();
}

int GetNumBySpiralIdx(int spiral_idx) {
	int x, y;
	tie(x, y) = spiral_points[spiral_idx];
	return grid[x][y];
}

// start_idx로부터 연속하여 같은 숫자로 이루어져 있는
// 가장 끝 index를 찾아 반환합니다. 
int GetEndIdxOfSameNum(int start_idx) {
	int end_idx = start_idx + 1;
	int curr_num = GetNumBySpiralIdx(start_idx);
	int end_of_array = (int)spiral_points.size();

	while (end_idx < end_of_array) {
		if (GetNumBySpiralIdx(end_idx) == curr_num)
			end_idx++;
		else
			break;
	}

	return end_idx - 1;
}

void Remove(int start_idx, int end_idx) {
	for (int i = start_idx; i <= end_idx; i++) {
		int x, y;
		tie(x, y) = spiral_points[i];
		ans += grid[x][y];
		grid[x][y] = 0;
	}
}

// 4번 이상 반복하여 나오는 구간을 지워줍니다.
bool Bomb() {
	bool did_explode = false;
	int curr_idx = 0;
	int end_of_array = (int)spiral_points.size();

	while (curr_idx < end_of_array) {
		int end_idx = GetEndIdxOfSameNum(curr_idx);
		int curr_num = GetNumBySpiralIdx(curr_idx);

		// 맨 끝에 도달하게 되면, 더이상 진행하지 않습니다.
		if (curr_num == 0)
			break;

		if (end_idx - curr_idx + 1 >= 4) {
			// 연속한 숫자의 개수가 4개 이상이면
			// 해당 구간을 지워줍니다.
			Remove(curr_idx, end_idx);
			did_explode = true;
		}

		// 그 다음 구간의 시작값으로 변경해줍니다.
		curr_idx = end_idx + 1;
	}

	return did_explode;
}

// 4번 이상 반복하여 나오는 구간을 계속 지워줍니다.
void Organize() {
	while (true) {
		// 4번 이상 나오는 구간을 터뜨려봅니다.
		bool keep_going = Bomb();

		if (!keep_going)
			break;

		// 지운 이후에는 다시 당겨서 채워줍니다.
		Pull();
	}
}

void LookAndSay() {
	// Step 1. temp 배열을 초기화합니다.
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			temp[i][j] = 0;

	// Step2. 보고 말하며 temp에 해당 값을 기록합니다.
	int temp_idx = 0;

	int curr_idx = 0;
	int end_of_array = (int)spiral_points.size();
	while (curr_idx < end_of_array) {
		int end_idx = GetEndIdxOfSameNum(curr_idx);

		// 연속하여 나온 숫자의 개수와 숫자 종류 값을 계산합니다.
		int contiguous_cnt = end_idx - curr_idx + 1;
		int curr_num = GetNumBySpiralIdx(curr_idx);

		// 맨 끝에 도달하게 되면, 더이상 진행하지 않습니다.
		if (curr_num == 0)
			break;

		// temp에 (개수, 종류) 순서대로 기록해줍니다.
		// 만약 격자를 벗어나면 종료합니다.
		if (temp_idx >= end_of_array)
			break;

		int tx, ty;
		tie(tx, ty) = spiral_points[temp_idx];
		temp[tx][ty] = contiguous_cnt;
		temp_idx++;

		if (temp_idx >= end_of_array)
			break;

		tie(tx, ty) = spiral_points[temp_idx];
		temp[tx][ty] = curr_num;
		temp_idx++;

		// 그 다음 구간의 시작값으로 변경해줍니다.
		curr_idx = end_idx + 1;
	}

	// Step 3. temp 값을 다시 grid에 옮겨줍니다.
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			grid[i][j] = temp[i][j];
}

void Simulate(int d, int p) {
	// Step 1. 공격하여 몬스터를 제거합니다.
	Attack(d, p);

	// Step 2. 4번 이상 반복하여 나오는 구간을 계속 지워줍니다.
	Organize();

	// Step 3. 보고 말하기 행동을 진행합니다.
	LookAndSay();
}

int main() {
	cin >> n >> m;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> grid[i][j];

	// 중심 탑을 기준으로 나선 모양으로 회전했을 때
	// 지나게 되는 위치의 좌표들을 순서대로 기록해 놓습니다.
	SearchSpiral();

	// m번에 걸쳐 시뮬레이션을 진행합니다.
	while (m--) {
		int d, p;
		cin >> d >> p;

		Simulate(d, p);
	}

	cout << ans;
}