#include <stdio.h>

int N;//�������� ��ǰ ����
int C[10];//BOX ����(1, 5, 10, 50, 100, 500, 1000, 3000, 6000, 12000 ��)
int D[10] = { 1, 5, 10, 50, 100, 500, 1000, 3000, 6000, 12000 };//BOX ����(1, 5, 10, 50, 100, 500, 1000, 3000, 6000, 12000 ��)

int sol[10];//������ BOX ����
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

	InputData();//	�Է� �Լ�

	//	�ڵ带 �ۼ��ϼ���
	ans = Sol();

	OutputData(ans);//	��� �Լ�

	return 0;
}