#include <iostream>

using namespace std;

int N, M;

#define MAX(a, b) ( a > b ? a: b)
#define MIN(a, b) ( a > b ? b: b)

typedef struct pos {
	int s, e;
} pos;

const int max_num = 1e5 + 10;

pos p[max_num];
int A[max_num];
long long int minNum = 987654321, maxNum =0;
long long int minDiff = 987654321, maxDiff = 0;

void input()
{
	cin >> N >> M;

	for (int i = 0; i < M; i++) {
		cin >> p[i].s >> p[i].e;
		A[p[i].s] = A[p[i].e]  = 1;
		minNum = MIN(minNum, p[i].s);
		maxNum = MAX(maxNum, p[i].e);
	}

	for (int i = 1; i < maxNum; i++) {
		minDiff = MIN(minDiff, p[i-1].e - p[i].s);
		maxDiff = MAX(maxDiff, p[i - 1].e - p[i].s);
	}
}

bool check(long long int d) {
	int idx = 0;
	long long last;
	last = p[0].s;
	for (int i = 1; i < N; i++) {
		while ((idx < M) && ((last + d) > p[idx].e)) idx++;
		if (idx == M) return false;
		last = (last + d < p[idx].s) ? (p[idx].s) : (last + d);
	}
	return true;
}

void sol()
{
	long long int s, e, m;
	s = minDiff;
	e = maxDiff;
	
	while ( s <= e) {
		m = (s + e) / 2;
		if (check(m)) {
			s = m + 1;
		}
		else {
			e = m - 1;
		}
	}
}

int main()
{
	freopen("A3_input.txt", "r", stdin);
	input();
	sol();
	return 0;
}