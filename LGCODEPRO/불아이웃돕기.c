#include <stdio.h>

int N;//보내려는 물품 개수
int C[10];//BOX 개수(1, 5, 10, 50, 100, 500, 1000, 3000, 6000, 12000 순)
int D[10] = { 1, 5, 10, 50, 100, 500, 1000, 3000, 6000, 12000 };//BOX 개수(1, 5, 10, 50, 100, 500, 1000, 3000, 6000, 12000 순)

int sol[10];//보내는 BOX 개수
int maxCnt = 0;

void InputData() {
	int i;
	scanf("%d", &N);
	for (i = 0; i < 10; i++) {
		scanf("%d", &C[i]);
	}
}
void OutputData(int ans) {
	int i;
	printf("%d\n", ans);
	for (i = 0; i < 10; i++) {
		printf("%d ", sol[i]);
	}
	printf("\n");
}

int Sol()
{
	int sum = 0;
	int retVal = 0;

	for (int i = 0; i < 10; i++) {
		sum += (C[i] * D[i]);
	}
	sum -= N;

	for (int i = 9; i >= 0; i--) {
		int cnt = sum / D[i];
		if (cnt > C[i]) cnt = C[i];
		sum -= cnt * D[i];
		sol[i] = C[i] - cnt;
		retVal += sol[i];
	}

	return retVal;
}

int main() {
	int ans = -1;

	InputData();//	입력 함수

	//	코드를 작성하세요
	ans = Sol();

	OutputData(ans);//	출력 함수

	return 0;
}