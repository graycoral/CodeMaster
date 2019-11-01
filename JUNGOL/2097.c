/*
지방에서 서울에 관광온 도훈이는 지하철 노선을 보고 깜짝 놀랐다.

노선이 엄청나게 복잡하기 때문이었다.

각 노선들이 서로 얽혀있어서 잘못하면 10분도 안걸리는 거리를 1시간 동안 갈 수도 있는 상황이었다.

어쩔 수 없이 도훈이​는 현재 숙소에서 관광할 목적지까지 가장 짧은 시간에 도착할 수 있는 경로와 시간을 표로 만들려고 한다.


단, 각 지하철역에서 관광지가 있고, 지하철을 갈아타는데 소요되는 시간은 없다고 가정한다.



첫줄에 N(3≤N≤100), M(1≤M≤N)을 입력 받는다.
N은 지하철역의 수, M은 원하는 목적역의 번호를 입력받는다.
둘째 줄부터 N개의 줄이 나오고, 각 줄에는 N개의 수 S가 입력된다.
i번째 줄에서 j번째 수 Sij는 i번역에서 j번 역까지 가는데 걸리는 시간이다.
1번 역이 숙소가 있는 역이고, Sij에서 i = j 일 때는 항상 0 이다. (0≤S≤100)

목적 역까지 가는데 걸리는 최소 시간과 최소시간으로 가는 최단경로를 출력한다.

5 5
0 2 2 5 9
2 0 3 4 8
2 3 0 7 6
5 4 7 0 5
9 5 6 5 0

8
1 3 5
*/

#include <stdio.h>
#define MAXN    ((int)100 +10)
int N, M;
int map[MAXN][MAXN];
int wp, rp;
int q[MAXN * MAXN];
int path[MAXN * MAXN];
int v[MAXN * MAXN];

int size(void) { return wp - rp; }
int empty(void) { return wp == rp; }
void input()
{
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &map[i][j]);
		}
	}
}

void push(int c, int sum, int pre) {
	if (v[c] <= sum) return;
	v[c] = sum;
	path[c] = pre;
	q[wp++] = c;
}

int pop() { return q[rp++]; }


void sol()
{
	for (int i = 0; i < MAXN * MAXN; i++)    v[i] = 0x7fff;

	push(1, map[1][1], 0);
	while (size() != 0) {
		int cur = pop();
		for (int i = 1; i <= N; i++) {
			if (cur == i)   continue;
			push(i, v[cur] + map[cur][i], cur);
		}
	}
}

void PRT(int idx)
{
	if (idx == 0)   return;
	PRT(path[idx]);
	printf("%d ", idx);
}

int main()
{
	input();
	sol();
	printf("%d\n", v[M]);
	PRT(M);
	return 0;
}