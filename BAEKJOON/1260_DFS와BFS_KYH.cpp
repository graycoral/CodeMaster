#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

#define MAXN	((int)1e4+10)
using namespace std;
int N, M, S;
vector<int> Map[1010];
queue<int> q;
int visited[MAXN];
int visited1[MAXN];

void input()
{
	int m, v;
	cin >> N >> M >> S;
	for (int i = 0; i < M; i++) {
		cin >> m >> v;
		Map[m].push_back(v);
		Map[v].push_back(m);
	}
}

void DFS(int idx)
{
	if (visited[idx] == 1)	return;
	visited[idx] = 1;
	cout << idx << " ";
	sort(Map[idx].begin(), Map[idx].end());
	for (auto it : Map[idx]) {
		DFS(it);
	}
}

void BFS()
{
	q.push(S);
	visited1[S] = 1;
	while (!q.empty()) {
		int cur = q.front(); q.pop();
		cout << cur << " ";
		sort(Map[cur].begin(), Map[cur].end());
		for (auto it : Map[cur]) {
			if (visited1[it] == 1)	continue;
			visited1[it] = 1;
			q.push(it);
		}
	}

}


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	input();
	DFS(S);
	cout << endl;
	BFS();

	return 0;
}