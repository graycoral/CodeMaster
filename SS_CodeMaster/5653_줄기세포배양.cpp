#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

priority_queue< pair< pair<int,int>, pair<pair<int, int>, int>>> q;
int T, N, M, K;
int arr[50][50];
int arr2[350][350];
int X[4] = { 1,-1,0,0 };
int Y[4] = { 0,0,1,-1 };
int visit[350][350];
int main() {
	freopen("5654_줄기세포배양.txt", "r", stdin);
	cin >> T;
	for (int i = 0; i < T; i++) {
		int CNT = 0;
		cin >> N >> M >> K;
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < M; k++) {
				cin >> arr[j][k];
				arr2[149 + j][149 + k] = arr[j][k];
				if (arr[j][k] != 0) {
					q.push(make_pair(make_pair(149 + j, 149 + k), make_pair(make_pair(arr[j][k], 0), 0)));
					visit[149 + j][149 + k] = 1;

				}
			}
		}

		while (!q.empty()) {
			int cx = q.top().first.second;//현재 x값
			int cy = q.top().first.first;//현재 y값
			int TI = q.top().second.first.first;//세포의 생명력
			int ct = q.top().second.first.second;//세포의 시간
			int cnt = q.top().second.second;  //현재 시간
			q.pop();
			if (TI != arr2[cy][cx]) { //arr에 값이 달라졌으면 우열에서 밀린 것이므로 out
				continue;
			}
			visit[cy][cx] = 1;// 세포 확산
			if (cnt == K) {//시간이 다 됐으면 큐에 남아있는 활성화 및 비활성화 세포들을 카운트
				CNT++;
				continue;
			}
			if (ct < 2 * TI - 1) {//세포가 완전히 죽기 전까지 계속 활성화시키기 위함
				q.push(make_pair(make_pair(cy, cx), make_pair(make_pair(TI, ct + 1), cnt + 1)));
			}
			if (ct == TI) {//세포분열 가능한 시간이 되면 분열
				for (int a = 0; a < 4; a++) {
					int nx = cx + X[a];
					int ny = cy + Y[a];
					if (nx >= 0 && nx < 350 && ny >= 0 && ny < 350 && visit[ny][nx] == 0 && (arr2[ny][nx] < TI || arr2[ny][nx] == 0)) {//만약 arr2에 있는 값이 TI보다 작거나(우열에서 이기면) 0이면 탐색
						arr2[ny][nx] = TI;
						q.push(make_pair(make_pair(ny, nx), make_pair(make_pair(TI, 0), cnt + 1)));
					}
				}
			}
		}
		cout << '#' << i + 1 << ' ' << CNT << endl;
		memset(arr, 0, sizeof(arr));
		memset(arr2, 0, sizeof(arr2));
		memset(visit, 0, sizeof(visit));
	}
}