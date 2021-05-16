#define _CRT_SECURE_NO_WARNINGS
#define SOL (3)
#include <iostream>
#include <iomanip>

using namespace std;

#if SOL == 1

const int maxN = 30 + 1;
const int maxM = 100 + 1;
const int deadNum = -1;

int map[maxN][maxN];
int visited[maxN][maxN];
int N, M;
int centerPosR;
int centerPosC;
int ans;

int dr[] = { 0, 1, 0, -1 };
int dc[] = { 1,0, -1, 0 };

typedef struct Round {

	int d, c;
} Round;

typedef struct Pos {

	int r, c;
} Pos;

Round rd[maxM];

void input()
{
	ans = 0;
	centerPosR = centerPosC = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			map[i][j] = visited[i][j] = 0;
		}
	}

	for (int i = 0; i < M; i++) {
		rd[i].d = rd[i].c = 0;
	}
	cin >> N >> M;
	centerPosC = centerPosR = N / 2;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}

	map[centerPosR][centerPosC] = 8;
	for (int i = 0; i < M; i++) {
		cin >> rd[i].d >> rd[i].c;
	}
}

#define DEBUG (1)
void show(int m, std::string str)
{
#if DEBUG
	cout << "=====================" << m << " " << str << "=====================" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i == centerPosR && j == centerPosC) {
				cout << setw(3) << 0;
			}
			else {
				cout << setw(3) << map[i][j];
			}
			
		}
		cout << endl;
	}
	cout << "==========================================" << endl;
#endif
}

bool invalidRange(int r, int c)
{
	if (r < 0 || c < 0 || r >= N || c >= N) return 1;
	else return 0;
}

void remove(int idx)
{
	Round rm = rd[idx];

	int nr = centerPosR; int nc = centerPosC;
	for (int i = 0; i < rm.c; i++) {
		nr += dr[rm.d]; nc += dc[rm.d];
		ans += map[nr][nc];
		if (invalidRange(nr, nc)) continue;
		if (map[nr][nc] == 0)	continue;
		map[nr][nc] = deadNum;
	}
}

int savedArray[maxN * maxN];
int savedArrayLen = 0;

void setList()
{
	int moveDic = 0;
	int moveCnt = 1;
	int dic[4] = { 2,1,0,3 };
	int curent_R = centerPosR; int curent_C = centerPosC;

	for (int i = 0; i < maxN * maxN; i++) {
		savedArray[i] = 0;
	}
	savedArrayLen = 0;

	while (curent_C || curent_R) {
		for (int i = 0; i < moveCnt; i++) {
			curent_R += dr[dic[moveDic]];
			curent_C += dc[dic[moveDic]];
			if (invalidRange(curent_R, curent_C)) break;
			if (map[curent_R][curent_C] == deadNum) {
				continue;
			}
			savedArray[savedArrayLen++] = map[curent_R][curent_C];
			if (curent_R == 0 && curent_C == 0)	break;
		}
		moveDic++;
		moveDic %= 4;
		if (moveDic == 0 || moveDic == 2)	moveCnt++;
	}
}

void Pull()
{
	int tmpArry[maxN* maxN] = { 0, };
	int tmpArryIdx = 0;

	for (int i = 0; i < savedArrayLen; i++) {
		if (savedArray[i] == 0)	continue;
		tmpArry[tmpArryIdx++] = savedArray[i];
	}

	for (int i = 0; i < savedArrayLen; i++) {
		savedArray[i] = tmpArry[i];
	}

	/*for (int i = startIdx; i < savedArrayLen-cnt; i++) {
		savedArray[i] = savedArray[i + cnt];
	}*/
	savedArrayLen = tmpArryIdx;
}

int removePattern()
{
	int retCnt = 0;

	for (int i = 0; i < savedArrayLen; i++) {
		int startValue = savedArray[i];
		int numCnt = 0;
		if (startValue == 0)	break;
		for (int j = i; j < savedArrayLen; j++) {
			if (startValue != savedArray[j])	break;
			numCnt++;
		}
		if (numCnt >= 4) {
			for (int idx = i; idx < i + numCnt; idx++) {
				savedArray[idx] = 0;
			}
			ans += (numCnt * startValue);			
			retCnt++;
		}
		i += (numCnt - 1);
	}

	Pull();

	return retCnt;
}

int reArrangeList[maxN * maxN];
int reArrangeListIdx = 0;
void reArrage()
{
	// init
	for (int i = 0; i < reArrangeListIdx; i++) {
		reArrangeList[i] = 0;
	}
	reArrangeListIdx = 0;
	
	for (int i = 0; i < savedArrayLen; i++) {
		int startValue = savedArray[i];
		int numCnt = 0;
		if (startValue == 0)	break;
		for (int j = i; j < savedArrayLen; j++) {
			if (startValue != savedArray[j])	break;
			numCnt++;
		}
		reArrangeList[reArrangeListIdx++] = numCnt;
		reArrangeList[reArrangeListIdx++] = startValue;
		
		i += (numCnt - 1);
	}
}

void buildNewMap()
{
	int dic[4] = { 2,1,0,3 };
	int current_R = centerPosR; int current_C = centerPosC;
	int moveCnt = 1;
	int moveDic = 0;
	int reArListIdx = 0;
	
	while (current_R || current_C) {
		for (int i = 0; i < moveCnt; i++) {
			current_R += dr[dic[moveDic]];
			current_C += dc[dic[moveDic]];
			//if (invalidRange(curent_R, curent_C)) break;
			map[current_R][current_C] = reArrangeList[reArListIdx++];
			if (current_R == 0 && current_C == 0)	break;
		}
		moveDic = (moveDic+1)%4;
		if (moveDic == 0 || moveDic == 2)	moveCnt++;
	}
}

void rebuild()
{
	setList();
	//show(ans, "setList");
	while (true) {
		if (removePattern() == 0)	break;
	}

	reArrage();
	//show(ans, "reArrage");
	buildNewMap();
	//show(ans, "buildNewMap");
}

void sol_2()
{
	int idx = M;
	int cnt = 0;
	while (idx--) {
		//show(M - idx, "init");
		remove(M - idx - 1);
		//show(M - idx, "remove");
		rebuild();
		show(ans, "Simulate");

		for (int r = 0; r < N; r++) {
			for (int c = 0; c < N; c++) {
				visited[r][c] = 0;
			}
		}
	}
}

int main()
{
	int test_case = 1;

	freopen("�̷�Ÿ�����潺.txt", "r", stdin);
	cin >> test_case;

	for (int i = 1; i <= test_case; i++) {
		input();
		
		sol_2();
		//cout << ans << endl;
		cout << "#" << i << " " << ans << endl;
	}

	return 0;
}

#elif SOL == 3
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>

using namespace std;

const int maxN = 25 + 1;
const int maxM = 100 + 1;

int map[maxN][maxN];
int visited[maxN][maxN];
int N, M;
int centerPosR;
int centerPosC;
int ans;

int dr[] = { 0, 1, 0, -1 };
int dc[] = { 1,0, -1, 0 };

typedef struct Round {

	int d, c;
} Round;

typedef struct Pos {

	int r, c;
} Pos;

Round rd[maxM];

void input()
{
	ans = 0;
	centerPosR = centerPosC = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			map[i][j] = visited[i][j] = 0;
		}
	}

	for (int i = 0; i < M; i++) {
		rd[i].d = rd[i].c = 0;
	}
	cin >> N >> M;
	centerPosC = centerPosR = N / 2;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}

	map[centerPosR][centerPosC] = 8;
	for (int i = 0; i < M; i++) {
		cin >> rd[i].d >> rd[i].c;
	}
}

#define DEBUG (1)
void show(int m, std::string str)
{
#if DEBUG
	cout << "=====================" << m << str << "=====================" << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << setw(3) << map[i][j];
		}
		cout << endl;
	}
	cout << "==========================================" << endl;
#endif
}

bool invalidRange(int r, int c)
{
	if (r < 0 || c < 0 || r >= N || c >= N) return 1;
	else return 0;
}

void remove(int idx)
{
	Round rm = rd[idx];

	int nr = centerPosR; int nc = centerPosC;
	for (int i = 0; i < rm.c; i++) {
		nr += dr[rm.d]; nc += dc[rm.d];
		if (invalidRange(nr, nc)) continue;
		if (map[nr][nc] == 0) continue;
		ans += map[nr][nc];
		map[nr][nc] = 0;
	}


}

void reorder()
{
	int oriArr[maxN * maxN + 1] = { 0 };
	int oriIdx = 0; int reIdx = 0;
	int moveCnt = 0;
	int dic[4] = { 2,1,0,3 };
	int nr = centerPosR; int nc = centerPosC;
	int idx = 1;

	while (idx <= N) {
		int k = 2;
		while (k--) {
			int moveDic = moveCnt % 4;
			int moveloopCnt = idx;
			while (moveloopCnt--) {
				nr += dr[dic[moveDic]];
				nc += dc[dic[moveDic]];
				if (invalidRange(nr, nc)) { continue; }
				if (map[nr][nc] == 0)    continue;
				oriArr[oriIdx++] = map[nr][nc];
			}
			moveCnt++;
		}
		idx++;
	}

	nr = centerPosR; nc = centerPosC;
	idx = 1;
	oriIdx = 0; moveCnt = 0;

	while (idx <= N) {
		int k = 2;
		while (k--) {
			int moveDic = moveCnt % 4;
			int moveloopCnt = idx;
			while (moveloopCnt--) {
				nr += dr[dic[moveDic]];
				nc += dc[dic[moveDic]];
				if (invalidRange(nr, nc)) { continue; }
				map[nr][nc] = oriArr[oriIdx++];
			}
			moveCnt++;
		}
		idx++;
	}
}

void checkPatter()
{
	int oriArr[maxN * maxN + 1] = { 0 };
	int reArr[maxN * maxN + 1] = { 0 };
	int oriIdx = 0; int reIdx = 0;
	int moveCnt = 0;
	int dic[4] = { 2,1,0,3 };
	int nr = centerPosR; int nc = centerPosC;
	int idx = 1;

	for (int i = 0; i < maxN * maxN + 1; i++) {
		oriArr[i] = 0;
	}

	while (idx <= N) {
		int k = 2;
		while (k--) {
			int moveDic = moveCnt % 4;
			int moveloopCnt = idx;
			while (moveloopCnt--) {
				nr += dr[dic[moveDic]];
				nc += dc[dic[moveDic]];
				if (invalidRange(nr, nc)) { continue; }
				if (map[nr][nc] == 0)    continue;
				oriArr[oriIdx++] = map[nr][nc];
			}
			moveCnt++;
		}
		idx++;
	}

	int cnt = 0;
	int falg = 1;
	while (falg) {
		int lenArr = oriIdx;
		int arrIdx = 0; int startIdx = 0;

		falg = 0;
		while (lenArr) {
			cnt = 0;
			int startvalue = oriArr[arrIdx];

			startIdx = arrIdx;
			if (startvalue == 0)	break;
			while (startvalue == oriArr[arrIdx]) {
				arrIdx++;
				cnt++;
			}
			if (cnt >= 4) {
				ans += (startvalue * cnt);
				for (int i = startIdx; i < oriIdx; i++) {
					oriArr[i] = oriArr[i + cnt];
				}
				arrIdx = startIdx + 1;
				falg++;
			}
			lenArr -= cnt;
		}
	}

	nr = centerPosR; nc = centerPosC;
	idx = 1;
	int len = 0; moveCnt = 0;

	while (idx <= N) {
		int k = 2;
		while (k--) {
			int moveDic = moveCnt % 4;
			int moveloopCnt = idx;
			while (moveloopCnt--) {
				nr += dr[dic[moveDic]];
				nc += dc[dic[moveDic]];
				if (invalidRange(nr, nc)) { continue; }
				map[nr][nc] = oriArr[len++];
			}
			moveCnt++;
		}
		idx++;
	}

}

void reArrange()
{
	int oriArr[maxN * maxN + 1] = { 0 };
	int reArr[maxN * maxN + 1] = { 0 };
	int oriIdx = 0; int reIdx = 0;
	int moveCnt = 0;
	int dic[4] = { 2,1,0,3 };
	int nr = centerPosR; int nc = centerPosC;
	int idx = 1;

	while (idx <= N) {
		int k = 2;
		while (k--) {
			int moveDic = moveCnt % 4;
			int moveloopCnt = idx;
			while (moveloopCnt--) {
				nr += dr[dic[moveDic]];
				nc += dc[dic[moveDic]];
				if (invalidRange(nr, nc)) { continue; }
				if (map[nr][nc] == 0)    continue;
				oriArr[oriIdx++] = map[nr][nc];
			}
			moveCnt++;
		}
		idx++;
	}

	int checkIdx = 0;
	for (int i = 0; i < oriIdx; i++) {
		int val = oriArr[i];
		int cnt = 0;

		while (val == oriArr[checkIdx]) {
			cnt++; checkIdx++;
		}
		reArr[reIdx++] = cnt;
		reArr[reIdx++] = oriArr[i];

		if (cnt != 1) i = checkIdx - 1;
	}

	//if (reIdx > oriIdx) return;

	nr = centerPosR; nc = centerPosC;
	idx = 1;
	oriIdx = 0; moveCnt = 0;

	while (idx <= N) {
		int k = 2;
		while (k--) {
			int moveDic = moveCnt % 4;
			int moveloopCnt = idx;
			while (moveloopCnt--) {
				nr += dr[dic[moveDic]];
				nc += dc[dic[moveDic]];
				if (invalidRange(nr, nc)) { continue; }
				map[nr][nc] = reArr[oriIdx++];
			}
			moveCnt++;
		}
		idx++;
	}
}

void sol()
{
	int idx = M;
	while (idx--) {
		show(M - idx, "init");
		remove(M - idx - 1);
		show(M - idx, "remove");
		reorder();
		show(M - idx, "reorder");
		checkPatter();
		show(M - idx, "checkpatter");
		reArrange();
		show(M - idx, "reArrange");

		for (int r = 0; r < N; r++) {
			for (int c = 0; c < N; c++) {
				visited[r][c] = 0;
			}
		}
	}
}

int main()
{
	int test_case = 1;

	/*freopen("�̷�Ÿ�����潺.txt", "r", stdin);
	cin >> test_case;*/

	for (int i = 1; i <= test_case; i++) {
		input();
		sol();
		cout << ans << endl;
		//cout << "#" << i << " " << ans << endl;
	}

	return 0;
}
#elif 2

#include <iostream>
#include <iomanip>
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


#define DEBUG (1)
void show(int m, std::string str)
{
#if DEBUG
	cout << "=====================" << m << " " << str << "=====================" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << setw(3) << grid[i][j];
		}
		cout << endl;
	}
	cout << "==========================================" << endl;
#endif
}

void SearchSpiral() {
	// ������ ���ư��� ������� 
	// ���� �Ʒ� ������ �� ������ �ǵ��� �����մϴ�.
	int dx[DIR_NUM] = { 0, 1, 0, -1 };
	int dy[DIR_NUM] = { -1, 0, 1, 0 };

	// ���� ��ġ�� ����, 
	// �ش� �������� �̵��� Ƚ���� �����մϴ�. 
	int curr_x = n / 2, curr_y = n / 2;
	int move_dir = 0, move_num = 1;

	while (curr_x || curr_y) {
		// move_num ��ŭ �̵��մϴ�.
		for (int i = 0; i < move_num; i++) {
			curr_x += dx[move_dir]; curr_y += dy[move_dir];
			spiral_points.push_back(make_pair(curr_x, curr_y));

			// �̵��ϴ� ���� (0, 0)���� ���� �Ǹ�,
			// �����̴� ���� �����մϴ�.
			if (!curr_x && !curr_y)
				break;
		}

		// ������ �ٲߴϴ�.
		move_dir = (move_dir + 1) % 4;
		// ���� ���� ������ ���� Ȥ�� �������� �� ��쿡��
		// Ư�� �������� �������� �� Ƚ���� 1 ������ŵ�ϴ�.
		if (move_dir == 0 || move_dir == 2)
			move_num++;
	}
}

void Pull() {
	// Step 1. temp �迭�� �ʱ�ȭ�մϴ�.
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			temp[i][j] = 0;

	// Step2. ���� ������� ����
	//        ������� ���� ������ temp�� ä���ݴϴ�.
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

	// Step 3. temp ���� �ٽ� grid�� �Ű��ݴϴ�.
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			grid[i][j] = temp[i][j];
}

void Attack(int d, int p) {
	// �������� �־��� ������� �� �� �� ��
	int dx[DIR_NUM] = { 0, 1,  0, -1 };
	int dy[DIR_NUM] = { 1, 0, -1,  0 };

	// Step 1. d �������� p������ ���͸� �����մϴ�.
	int center_x = n / 2, center_y = n / 2;
	for (int dist = 1; dist <= p; dist++) {
		int nx = center_x + dx[d] * dist;
		int ny = center_y + dy[d] * dist;

		ans += grid[nx][ny];
		grid[nx][ny] = 0;
	}

	// Step2. ��� �ִ� �ڸ��� ��ܼ� ä���ݴϴ�.
	Pull();
}

int GetNumBySpiralIdx(int spiral_idx) {
	int x, y;
	tie(x, y) = spiral_points[spiral_idx];
	return grid[x][y];
}

// start_idx�κ��� �����Ͽ� ���� ���ڷ� �̷���� �ִ�
// ���� �� index�� ã�� ��ȯ�մϴ�. 
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

// 4�� �̻� �ݺ��Ͽ� ������ ������ �����ݴϴ�.
bool Bomb() {
	bool did_explode = false;
	int curr_idx = 0;
	int end_of_array = (int)spiral_points.size();

	while (curr_idx < end_of_array) {
		int end_idx = GetEndIdxOfSameNum(curr_idx);
		int curr_num = GetNumBySpiralIdx(curr_idx);

		// �� ���� �����ϰ� �Ǹ�, ���̻� �������� �ʽ��ϴ�.
		if (curr_num == 0)
			break;

		if (end_idx - curr_idx + 1 >= 4) {
			// ������ ������ ������ 4�� �̻��̸�
			// �ش� ������ �����ݴϴ�.
			Remove(curr_idx, end_idx);
			did_explode = true;
		}

		// �� ���� ������ ���۰����� �������ݴϴ�.
		curr_idx = end_idx + 1;
	}

	return did_explode;
}

// 4�� �̻� �ݺ��Ͽ� ������ ������ ��� �����ݴϴ�.
void Organize() {
	while (true) {
		// 4�� �̻� ������ ������ �Ͷ߷����ϴ�.
		bool keep_going = Bomb();

		if (!keep_going)
			break;

		// ���� ���Ŀ��� �ٽ� ��ܼ� ä���ݴϴ�.
		Pull();
	}
}

void LookAndSay() {
	// Step 1. temp �迭�� �ʱ�ȭ�մϴ�.
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			temp[i][j] = 0;

	// Step2. ���� ���ϸ� temp�� �ش� ���� ����մϴ�.
	int temp_idx = 0;

	int curr_idx = 0;
	int end_of_array = (int)spiral_points.size();
	while (curr_idx < end_of_array) {
		int end_idx = GetEndIdxOfSameNum(curr_idx);

		// �����Ͽ� ���� ������ ������ ���� ���� ���� ����մϴ�.
		int contiguous_cnt = end_idx - curr_idx + 1;
		int curr_num = GetNumBySpiralIdx(curr_idx);

		// �� ���� �����ϰ� �Ǹ�, ���̻� �������� �ʽ��ϴ�.
		if (curr_num == 0)
			break;

		// temp�� (����, ����) ������� ������ݴϴ�.
		// ���� ���ڸ� ����� �����մϴ�.
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

		// �� ���� ������ ���۰����� �������ݴϴ�.
		curr_idx = end_idx + 1;
	}

	// Step 3. temp ���� �ٽ� grid�� �Ű��ݴϴ�.
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			grid[i][j] = temp[i][j];
}

void Simulate(int d, int p) {
	// Step 1. �����Ͽ� ���͸� �����մϴ�.
	Attack(d, p);

	// Step 2. 4�� �̻� �ݺ��Ͽ� ������ ������ ��� �����ݴϴ�.
	Organize();

	// Step 3. ���� ���ϱ� �ൿ�� �����մϴ�.
	LookAndSay();
}

int main() {
	int test_case = 1;

	freopen("�̷�Ÿ�����潺.txt", "r", stdin);
	cin >> test_case;

	cin >> n >> m;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> grid[i][j];

	// �߽� ž�� �������� ���� ������� ȸ������ ��
	// ������ �Ǵ� ��ġ�� ��ǥ���� ������� ����� �����ϴ�.
	SearchSpiral();

	// m���� ���� �ùķ��̼��� �����մϴ�.
	int cnt = 0;
	while (m--) {
		int d, p;
		cin >> d >> p;

		Simulate(d, p);
		show(ans, "Simulate");
	}

	cout << ans;
}
#endif
