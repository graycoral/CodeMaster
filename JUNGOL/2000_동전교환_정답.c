//C3 : 동전교환
#include <stdio.h>
#define INF ((int)1e5)
#define MAXN (10+2)
#define MAXW ((int)64e3 + 2)
#define TEST 4
//(1:DFS, 2:memoization, 3:dynamic(2차원배열), 4:dynamic(1차원배열))
int N;//동전 단계수
int coin[MAXN];//동전 단위
int W;//잔돈
#if TEST == 1
int sol;//최소 동전수
void DFS(int n, int w, int cnt) {
	int i;
	if (sol <= cnt) return;//가지치기
	if (w == 0) {//종료조건 완성
		sol = cnt;
		return;
	}
	if (n > N) return;//종료조건
	for (i = w / coin[n]; i >= 0; i--) {
		DFS(n + 1, w - i * coin[n], cnt + i);
	}
}
int solve(void) {
	sol = INF;
	DFS(1, W, 0);//동전 인덱스, 잔돈, 필요한 동전 수
	return sol;
}
#elif TEST == 2
#define NOTSOLVED (-1)
int dp[MAXN][MAXW];//[동전단위][잔돈]
//i번째 동전을 포함해서 j잔돈을 만들때 사용되는 최소 동전 수
int memoi(int n, int w) {
	int cnt;
	if (dp[n][w] == NOTSOLVED) {
		dp[n][w] = memoi(n - 1, w);
		if (w >= coin[n]) {//n번째 동전보다 잔돈이 크거나 같아야 함
			cnt = memoi(n, w - coin[n]) + 1;
			if (dp[n][w] > cnt) dp[n][w] = cnt;
		}
	}
	return dp[n][w];
}
int solve(void) {
	int i, j;
	//초기화 필요(dp배열)
	for (j = 1; j <= W; j++) dp[0][j] = INF;//동전없으면 만들수없음(불가능)
	for (i = 0; i <= N; i++) dp[i][0] = 0;//0원은 만들수있음(0개필요)
	for (i = 1; i <= N; i++) {//동전 단위 인덱스
		for (j = 1; j <= W; j++) {//잔돈 인덱스
			dp[i][j] = NOTSOLVED;//계산 안함으로 표시
		}
	}
	return memoi(N, W);
}
#elif TEST == 3
int dp[MAXN][MAXW];//[동전단위][잔돈]
//i번째 동전을 포함해서 j잔돈을 만들때 사용되는 최소 동전 수
int solve(void) {
	int i, j;
	//초기화
	for (j = 1; j <= W; j++) dp[0][j] = INF;//동전없으면 만들수없음(불가능)
	for (i = 0; i <= N; i++) dp[i][0] = 0;//0원은 만들수있음(0개필요)
	for (i = 1; i <= N; i++) {//동전 단위 인덱스
		for (j = 1; j <= W; j++) {//잔돈 인덱스
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
int dp[MAXW];//[잔돈]
//i번째 동전을 포함해서 j잔돈을 만들때 사용되는 최소 동전 수
int solve(void) {
	int i, j;
	//초기화
	for (j = 1; j <= W; j++) dp[j] = INF;//동전없으면 만들수없음(불가능)
	dp[0] = 0;//0원은 만들수있음(0개필요)
	for (i = 1; i <= N; i++) {//동전 단위 인덱스
		for (j = coin[i]; j <= W; j++) {//잔돈 인덱스
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
#if 0 // 설명
int dp[N][W];//i번째 동전을 포함해서 j잔돈을 만들때 사용되는 최소 동전 수
dp[n][w] = min dp[n - 1][w];//n번째 동전을 빼고 나머지 동전으로 w원을 만드는 수
dp[n - 1][w - coin[n] * 1] + 1;//n번째 동전 1개 사용
dp[n - 1][w - coin[n] * 2] + 2;//n번째 동전 2개 사용
dp[n - 1][w - coin[n] * 3] + 3;//n번째 동전 3개 사용
...
dp[n - 1][w - coin[n] * k] + k;//n번째 동전 k개 사용

dp[n - 1][w] = min dp[n - 2][w];//n-1번째 동전을 빼고 나머지 동전으로 w원을 만드는 수
dp[n - 2][w - coin[n - 1] * 1] + 1;//n-1번째 동전 1개 사용
dp[n - 2][w - coin[n - 1] * 2] + 2;//n-1번째 동전 2개 사용
dp[n - 2][w - coin[n - 1] * 3] + 3;//n-1번째 동전 3개 사용
...
dp[n - 2][w - coin[n - 1] * k] + k;//n-1번째 동전 k개 사용

최종 점화식
dp[n][w] = min dp[n - 1][w];//n번째 동전 0개 사용
dp[n][w - coin[n]] + 1;//n번째 동전 1개더(?) 사용
//(실제로는 여러개 사용했을수도 있음)
#endif