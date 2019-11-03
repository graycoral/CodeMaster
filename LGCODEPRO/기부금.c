#include <stdio.h>

int N;//���� ��
int M;//��α� �Ѿ�
int A[1000010];//���� �� ������

int maxM;
int maxm;

void Input_Data(void) {
	int i;
	scanf("%d %d", &N, &M);
	for (i = 0; i < N; i++) {
		scanf("%d", &A[i]);
		if (maxm < A[i])	maxm = A[i];
	}
}

void Solve()
{
	int s = 0;
	int e = maxm;

	while (s <= e) {
		int n = (s + e) / 2;
		int sum = 0;
		for (int i = 0; i < N; i++) {
			if (n < A[i]) {
				sum += A[i] - n;
				if (sum >= M)	break;
			}
		}
		if (sum >= M) {
			if (maxM <= n)	maxM = n;
			s = n + 1;
		}
		else {
			e = n - 1;
		}
	}
}

int main(void) {
	int ans = 0;
	Input_Data();		//	�Է� �Լ�
	Solve();
	ans = maxM;
	//	�ڵ带 �ۼ��ϼ���
	printf("%d\n", ans);		//	���� ���
	return 0;
}
