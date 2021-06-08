#include <iostream>
#include <algorithm>

using namespace std;

#define MIN(a, b) ( a > b ? b : a)

const int max_num = 100;
const int INF = 987654321;

int startR, startC;
int endR, endC;

int r[max_num];
int c[max_num];

int N;

int min_sum = INF;
int visited[max_num];
//int test[100];

void input()
{
	for (int i = 0; i < N; i++) {
		r[i] = c[i] = visited[i] = 0;
	}

	min_sum = INF;

	cin >> N;

	cin >> startR >> startC;
	cin >> endR >> endC;

	for (int i = 0; i < N; i++) {
		cin >> r[i] >> c[i];
	}
}

void combi(int idx, int start, int sum)
{
	if (sum > min_sum)	return;
	if (idx == N) {
		min_sum = MIN(min_sum, sum + abs(r[start] - endR) + abs(c[start] - endC));
		return;
	}

	for (int i = 0; i < N ; i++) {
		if (visited[i] == 1) continue;
		
		if (idx == -1) {
			combi(0, i, abs(startR - r[i]) + abs(startC - c[i]));
		}
		else {
			visited[i] = 1;
			//test[idx] = i;
			combi(idx + 1, i, sum + abs(r[start] - r[i]) + abs(c[start] - c[i]));
			visited[i] = 0;
		}
	}
}

int main()
{
	int test_case = 1;
	//freopen("swea_1247_input.txt", "r", stdin);
	cin >> test_case;
	for (int i = 1; i <= test_case; i++) {
		input();
		combi(-1, 0, 0);
		cout << "#" << i << " " << min_sum << endl;
	}
	return 0;
}