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

// ���� ���̰ų�, ������ ��ź�� ��쿡�� �̵��� �����մϴ�.
bool CanGo(int x, int y, int color) {
	return InRange(x, y) && !visited[x][y] && (
		grid[x][y] == color || grid[x][y] == RED
		);
}

void BFS(int x, int y, int color) {
	// visited ���� �ʱ�ȭ�մϴ�.
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			visited[i][j] = false;

	// �������� ǥ���մϴ�.
	visited[x][y] = true;
	bfs_q.push(make_pair(x, y));

	int dx[DIR_NUM] = { 0, 1, 0, -1 };
	int dy[DIR_NUM] = { 1, 0, -1, 0 };

	// BFS Ž���� �����մϴ�.
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

// (x, y) ������ �������� bundle ������ ����� ��ȯ�մϴ�.
Bundle GetBundle(int x, int y) {
	// Step1. (x, y)�� �������� bfs Ž���� �����մϴ�.
	BFS(x, y, grid[x][y]);

	// Step2. bundle ������ ����� ��ȯ�մϴ�.
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

// �켱������ ���� ���� ����ϱ� ����
// (��ź ������ ũ��, -������ ��ź�� ��, �� ��ȣ, -�� ��ȣ)
// ������� ���� �־��ݴϴ�.
Bundle FindBestBundle() {
	Bundle best_bundle = EMPTY_BUNDLE;

	// �������� �ƴ� ��ź�鿡 ���ؼ��� ���� Ž���մϴ�.
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
	// �߷� �ۿ��� ���� �����ϱ� ����
	// temp �迭�� Ȱ���մϴ�.
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			temp[i][j] = EMPTY;

	// Step2.
	for (int j = 0; j < n; j++) {
		// �Ʒ����� ���� �ö���鼭
		// �ش� ��ġ�� ��ź�� �ִ� ��쿡�� temp�� 
		// �׾��ִ� ������ �ڵ带 �ۼ��� �� �ֽ��ϴ�.

		// ��, ���� �ִ� ��쿡��
		// �������� ���� �� �ֵ��� �մϴ�.
		int last_idx = n - 1;
		for (int i = n - 1; i >= 0; i--) {
			if (grid[i][j] == EMPTY)
				continue;
			if (grid[i][j] == ROCK)
				last_idx = i;
			temp[last_idx--][j] = grid[i][j];

		}
	}

	// Step3. �ٽ� temp �迭�� �Ű��ݴϴ�.
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			grid[i][j] = temp[i][j];
	
	show("gravity");
}

// �ݽð� �������� 90' ��ŭ ȸ���մϴ�.
void Rotate() {
	// Step1. 
	// ȸ�� ������ ���� �����ϱ� ����
	// temp �迭�� Ȱ���մϴ�.
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			temp[i][j] = EMPTY;

	// Step2.
	// ���� ���ڸ� �ݽð� �������� 90�� ȸ������ ���� �����
	// temp�� �������ݴϴ�.
	for (int j = n - 1; j >= 0; j--)
		for (int i = 0; i < n; i++)
			temp[n - 1 - j][i] = grid[i][j];

	// Step3.
	// �ٽ� temp �迭�� �Ű��ݴϴ�.
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			grid[i][j] = temp[i][j];

	show("reorder");
}

void Clean(int x, int y) {
	// Step1. (x, y)�� �������� �������� ��ź ������ ǥ���մϴ�.
	BFS(x, y, grid[x][y]);

	// Step2. ��ź���� ���� �����ݴϴ�.
	Remove(grid[x][y]);

	// Step3. �߷��� �ۿ��մϴ�.
	Gravity();
}

bool Simulate() {
	// Step1. ũ�Ⱑ �ִ��� ��ź ������ ã���ϴ�.
	Bundle best_bundle = FindBestBundle();

	int bomb_cnt, x, y;
	tie(bomb_cnt, ignore, x, y) = best_bundle;

	// ���� ��ź ������ ���ٸ�, �����մϴ�.
	if (best_bundle == EMPTY_BUNDLE || bomb_cnt <= 1)
		return false;

	// Step2. ���õ� ��ź ������ �ش��ϴ� ��ź���� ���� ���� ��
	//        �߷��� �ۿ��մϴ�.
	ans += bomb_cnt * bomb_cnt;
	Clean(x, -y);

	// Step3. �ݽð� �������� 90' ��ŭ ȸ���մϴ�.
	Rotate();

	// Step4. �߷��� �ۿ��մϴ�.
	Gravity();	
	return true;
}

int main() {
	int test_case = 1;

	freopen("������ź.txt", "r", stdin);
	cin >> test_case;
	cin >> n >> m;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> grid[i][j];

	// ������ ������ �ùķ��̼��� �ݺ��մϴ�.
	while (true) {
		bool keep_going = Simulate();

		if (!keep_going)
			break;
	}

	cout << ans;
}