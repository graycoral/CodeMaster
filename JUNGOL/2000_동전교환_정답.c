//C3 : ������ȯ
#include <stdio.h>
#define INF ((int)1e5)
#define MAXN (10+2)
#define MAXW ((int)64e3 + 2)
#define TEST 4
//(1:DFS, 2:memoization, 3:dynamic(2�����迭), 4:dynamic(1�����迭))
int N;//���� �ܰ��
int coin[MAXN];//���� ����
int W;//�ܵ�
#if TEST == 1
int sol;//�ּ� ������
void DFS(int n, int w, int cnt) {
	int i;
	if (sol <= cnt) return;//����ġ��
	if (w == 0) {//�������� �ϼ�
		sol = cnt;
		return;
	}
	if (n > N) return;//��������
	for (i = w / coin[n]; i >= 0; i--) {
		DFS(n + 1, w - i * coin[n], cnt + i);
	}
}
int solve(void) {
	sol = INF;
	DFS(1, W, 0);//���� �ε���, �ܵ�, �ʿ��� ���� ��
	return sol;
}
#elif TEST == 2
#define NOTSOLVED (-1)
int dp[MAXN][MAXW];//[��������][�ܵ�]
//i��° ������ �����ؼ� j�ܵ��� ���鶧 ���Ǵ� �ּ� ���� ��
int memoi(int n, int w) {
	int cnt;
	if (dp[n][w] == NOTSOLVED) {
		dp[n][w] = memoi(n - 1, w);
		if (w >= coin[n]) {//n��° �������� �ܵ��� ũ�ų� ���ƾ� ��
			cnt = memoi(n, w - coin[n]) + 1;
			if (dp[n][w] > cnt) dp[n][w] = cnt;
		}
	}
	return dp[n][w];
}
int solve(void) {
	int i, j;
	//�ʱ�ȭ �ʿ�(dp�迭)
	for (j = 1; j <= W; j++) dp[0][j] = INF;//���������� ���������(�Ұ���)
	for (i = 0; i <= N; i++) dp[i][0] = 0;//0���� ���������(0���ʿ�)
	for (i = 1; i <= N; i++) {//���� ���� �ε���
		for (j = 1; j <= W; j++) {//�ܵ� �ε���
			dp[i][j] = NOTSOLVED;//��� �������� ǥ��
		}
	}
	return memoi(N, W);
}
#elif TEST == 3
int dp[MAXN][MAXW];//[��������][�ܵ�]
//i��° ������ �����ؼ� j�ܵ��� ���鶧 ���Ǵ� �ּ� ���� ��
int solve(void) {
	int i, j;
	//�ʱ�ȭ
	for (j = 1; j <= W; j++) dp[0][j] = INF;//���������� ���������(�Ұ���)
	for (i = 0; i <= N; i++) dp[i][0] = 0;//0���� ���������(0���ʿ�)
	for (i = 1; i <= N; i++) {//���� ���� �ε���
		for (j = 1; j <= W; j++) {//�ܵ� �ε���
			dp[i][j] = dp[i - 1][j];
			if (j >= coin[i]) {
				if (dp[i][j] > dp[i][j - coin[i]] + 1) {
					dp[i][j] = dp[i][j - coin[i]] + 1;
				}
			}
		}
	}
	return dp[N][W];
}
#else
int dp[MAXW];//[�ܵ�]
//i��° ������ �����ؼ� j�ܵ��� ���鶧 ���Ǵ� �ּ� ���� ��
int solve(void) {
	int i, j;
	//�ʱ�ȭ
	for (j = 1; j <= W; j++) dp[j] = INF;//���������� ���������(�Ұ���)
	dp[0] = 0;//0���� ���������(0���ʿ�)
	for (i = 1; i <= N; i++) {//���� ���� �ε���
		for (j = coin[i]; j <= W; j++) {//�ܵ� �ε���
			if (dp[j] > dp[j - coin[i]] + 1) {
				dp[j] = dp[j - coin[i]] + 1;
			}
		}
	}
	return dp[W];
}
#endif // TEST
void InputData(void) {
	int i;
	scanf("%d", &N);
	for (i = 1; i <= N; i++) {
		scanf("%d", &coin[i]);
	}
	scanf("%d", &W);
}
int main(void) {
	int ans;
	InputData();
	ans = solve();
	if (ans == INF) printf("impossible\n");
	else printf("%d\n", ans);
	return 0;
}
#if 0 // ����
int dp[N][W];//i��° ������ �����ؼ� j�ܵ��� ���鶧 ���Ǵ� �ּ� ���� ��
dp[n][w] = min dp[n - 1][w];//n��° ������ ���� ������ �������� w���� ����� ��
dp[n - 1][w - coin[n] * 1] + 1;//n��° ���� 1�� ���
dp[n - 1][w - coin[n] * 2] + 2;//n��° ���� 2�� ���
dp[n - 1][w - coin[n] * 3] + 3;//n��° ���� 3�� ���
...
dp[n - 1][w - coin[n] * k] + k;//n��° ���� k�� ���

dp[n - 1][w] = min dp[n - 2][w];//n-1��° ������ ���� ������ �������� w���� ����� ��
dp[n - 2][w - coin[n - 1] * 1] + 1;//n-1��° ���� 1�� ���
dp[n - 2][w - coin[n - 1] * 2] + 2;//n-1��° ���� 2�� ���
dp[n - 2][w - coin[n - 1] * 3] + 3;//n-1��° ���� 3�� ���
...
dp[n - 2][w - coin[n - 1] * k] + k;//n-1��° ���� k�� ���

���� ��ȭ��
dp[n][w] = min dp[n - 1][w];//n��° ���� 0�� ���
dp[n][w - coin[n]] + 1;//n��° ���� 1����(?) ���
//(�����δ� ������ ����������� ����)
#endif