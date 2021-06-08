#include <iostream>

using namespace std;

#define MIN(a,b) (a >  b ? b :a)

const long int max_num = 1e5 + 10;
const int INF = 987654321;

int map[510][510];
int N, M;

void input()
{
	cin >> N >> M;

	for (int i = 0; i < M; i++) {
		int start, end, cost;
		cin >> start >> end >> cost;
		map[start][end] = cost;
	}
}

void bellmanFord(int start)
{
	int upper[510];
	bool updated = false;

	for (int i = 0; i < 510; i++) upper[i] = INF;
	upper[start] = 0;

	for (int i = 0; i < N; i++) {
		updated = false;
		for (int here = 1; here <= N; here++) {
			for (int j = 1; j <= N; j++) {
				if (here == j)	continue;
				if (upper[here] > upper[here] + map[here][j]) {
					upper[here] = upper[here] + map[here][j];
					updated = true;
				}
			}
		}
		if (!updated)	break;
		if (updated) {
			for (int i = 0; i < max_num; i++) upper[i] = INF;
		}
	}

	for (int i = 2; i <= N; i++) {
		cout << upper[i] << endl;
	}
}

int main()
{
	freopen("11657_input.txt", "r", stdin);
	input();
	bellmanFord(1);
	return 0;
}