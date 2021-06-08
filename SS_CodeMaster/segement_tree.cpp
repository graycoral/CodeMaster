#include <cstdio>
#define ll long long

int N, M, K;
ll tree[4000000];
ll in[1000001];

ll get(int node, int left, int right, int start, int end) {
	if (end<left || start>right) return 0;
	else if (start >= left && end <= right) return tree[node];
	return 	get(2 * node, left, right, start, (start + end) / 2) +
		get(2 * node + 1, left, right, ((start + end) / 2) + 1, end);

}

void update(ll val, int node, int left, int right, int start, int end) {
	if (end<left || start>right) return;
	else if (start == end) {
		tree[node] += val;
		return;
	}
	update(val, 2 * node, left, right, start, ((start + end) / 2));
	update(val, 2 * node + 1, left, right, ((start + end) / 2) + 1, end);
	tree[node] += val;
	return;
}

int main() {
	scanf("%d %d %d", &N, &M, &K);
	for (int i = 1; i <= N; i++) {
		scanf("%lld", &in[i]);
		update(in[i], 1, i, i, 1, N);
	}

	for (int i = 0; i < M + K; i++) {
		int flag;
		long long b, c;
		scanf("%d %lld %lld", &flag, &b, &c);
		if (flag == 1) {
			update(c - in[b], 1, b, b, 1, N);
			in[b] = c;
		}
		else {
			printf("%lld\n", get(1, b, c, 1, N));
		}
	}
}

//[출처] 알고리즘 세그먼트 트리(1) | 작성자 whtrb_study