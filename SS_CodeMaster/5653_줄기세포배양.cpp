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
	freopen("5654_�ٱ⼼�����.txt", "r", stdin);
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
			int cx = q.top().first.second;//���� x��
			int cy = q.top().first.first;//���� y��
			int TI = q.top().second.first.first;//������ �����
			int ct = q.top().second.first.second;//������ �ð�
			int cnt = q.top().second.second;  //���� �ð�
			q.pop();
			if (TI != arr2[cy][cx]) { //arr�� ���� �޶������� �쿭���� �и� ���̹Ƿ� out
				continue;
			}
			visit[cy][cx] = 1;// ���� Ȯ��
			if (cnt == K) {//�ð��� �� ������ ť�� �����ִ� Ȱ��ȭ �� ��Ȱ��ȭ �������� ī��Ʈ
				CNT++;
				continue;
			}
			if (ct < 2 * TI - 1) {//������ ������ �ױ� ������ ��� Ȱ��ȭ��Ű�� ����
				q.push(make_pair(make_pair(cy, cx), make_pair(make_pair(TI, ct + 1), cnt + 1)));
			}
			if (ct == TI) {//�����п� ������ �ð��� �Ǹ� �п�
				for (int a = 0; a < 4; a++) {
					int nx = cx + X[a];
					int ny = cy + Y[a];
					if (nx >= 0 && nx < 350 && ny >= 0 && ny < 350 && visit[ny][nx] == 0 && (arr2[ny][nx] < TI || arr2[ny][nx] == 0)) {//���� arr2�� �ִ� ���� TI���� �۰ų�(�쿭���� �̱��) 0�̸� Ž��
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