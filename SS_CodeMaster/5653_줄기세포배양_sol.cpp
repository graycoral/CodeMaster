#include <iostream>
#include <queue>
using namespace std;

int N, M, K;
struct Cell {
	int state = -1;
	int life;
	int unActiveTime;
	int activeTime;
};
Cell box[350][350];

int dr[4] = { -1,1,0,0 };
int dc[4] = { 0,0,-1,1 };

int main() {
	int tc;
	cin >> tc;
	for (int t = 1; t <= tc; t++) {
		Cell initCell;
		initCell.state = -1;
		initCell.life = 0;
		initCell.unActiveTime = 0;
		initCell.activeTime = 0;
		for (int i = 0; i < 350; i++) {
			for (int j = 0; j < 350; j++) {
				box[i][j] = initCell;
			}
		}
		cin >> N >> M >> K;
		for (int r = 0; r < N; r++) {
			for (int c = 0; c < M; c++) {
				int life;
				cin >> life;
				if (life > 0) {
					Cell cell;
					cell.life = life;
					cell.unActiveTime = life;
					cell.activeTime = life;
					cell.state = 0;
					box[r + 150][c + 150] = cell;
				}
			}
		}
		int time = 0;
		while (time < K) {
			queue<pair<int, int>> activeCells;
			for (int r = 0; r < 350; r++) {
				for (int c = 0; c < 350; c++) {
					if (box[r][c].state == 0) {
						if (box[r][c].unActiveTime > 0) {
							box[r][c].unActiveTime--;
						}
						if (box[r][c].unActiveTime == 0) {
							box[r][c].state = 1;
						}
					}
					else if (box[r][c].state == 1) {
						if (box[r][c].activeTime > 0) {
							activeCells.push({ r,c });
							box[r][c].activeTime--;
						}
						if (box[r][c].activeTime == 0) {
							box[r][c].state = 2;
						}
					}
				}
			}
			while (!activeCells.empty()) {
				int r = activeCells.front().first;
				int c = activeCells.front().second;
				activeCells.pop();
				for (int i = 0; i < 4; i++) {
					int nr = r + dr[i];
					int nc = c + dc[i];
					if (nr < 0 || nr >= 350 || nc < 0 || nc >= 350) continue;
					if (box[nr][nc].state < 0) {
						box[nr][nc].state = 0;
						box[nr][nc].life = box[r][c].life;
						box[nr][nc].unActiveTime = box[r][c].life;
						box[nr][nc].activeTime = box[r][c].life;
					}
					else if (box[nr][nc].state == 0 && box[nr][nc].life == box[nr][nc].unActiveTime) {
						if (box[nr][nc].life < box[r][c].life) {
							box[nr][nc].life = box[r][c].life;
							box[nr][nc].unActiveTime = box[r][c].life;
							box[nr][nc].activeTime = box[r][c].life;
						}
					}
				}
			}
			time++;
		}
		int ans = 0;
		for (int i = 0; i < 350; i++) {
			for (int j = 0; j < 350; j++) {
				if (box[i][j].state == 0 || box[i][j].state == 1)
					ans++;
			}
		}
		cout << "#" << t << " " << ans << endl;
	}
	return 0;
}

#if 0
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

int N, M, K, map[650][650];

struct State {
	int x, y, t;
	bool operator<(const State& o)const {
		return t < o.t;
	}
} q[250000];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int t;
	cin >> t;
	for (int tc = 1; tc <= t; tc++) {
		cin >> N >> M >> K;
		priority_queue<State> pq;
		memset(map, 0, sizeof(map));
		for (int i = K; i < K + N; i++) {
			for (int j = K; j < K + M; j++) {
				cin >> map[i][j];
				if (map[i][j] != 0)
					pq.push({ i, j, map[i][j] });
			}
		}
		int front = -1, rear = -1, ret = 0;
		while (!pq.empty()) {
			q[++rear] = pq.top(), pq.pop();
		}
		while (K--) {
			int sz = rear - front;
			while (sz--) {
				State cur = q[++front];
				if (cur.t-- != 0) {
					q[++rear] = { cur.x, cur.y, cur.t };
				}
				else {
					if (map[cur.x][cur.y] - 1 > K) ret++;
					for (int d = 0; d < 4; d++) {
						int nx = cur.x + dx[d];
						int ny = cur.y + dy[d];
						if (map[nx][ny])continue;
						map[nx][ny] = map[cur.x][cur.y];
						q[++rear] = { nx, ny, map[nx][ny] };
					}
				}
			}
		}
		cout << "#" << tc << " " << ret + rear - front << "\n";
	}
	return 0;
}
#endif