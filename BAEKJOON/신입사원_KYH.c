#include <stdio.h>
#include <stdlib.h>

#define MAXN	((int)1e5+10)
int T, N;
struct data {
	int a, b;
};

struct data Q[MAXN];

void input()
{
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &Q[i].a, &Q[i].b);
	}
}

int compare(const void* a, const void* b)    // �������� �� �Լ� ����
{
	struct data num1 = *(struct data*)a;    // void �����͸� int �����ͷ� ��ȯ�� �� �������Ͽ� ���� ������
	struct data num2 = *(struct data*)b;    // void �����͸� int �����ͷ� ��ȯ�� �� �������Ͽ� ���� ������	

	return num1.a - num2.a;    // a�� b�� ���� ���� 0 ��ȯ
}

int sol()
{
	int retVal = 0;
	qsort(Q, N, sizeof(Q[0]), compare);
	int prev = Q[0].b;

	for (int i = 1; i < N; i++) {
		if (prev > Q[i].b) {
			retVal++;
			prev = Q[i].b;
		}
	}

	return retVal + 1;
}

int main()
{
	scanf("%d", &T);
	for (int i = 0; i < T; i++) {
		input();
		printf("%d\n", sol());
	}
	return 0;
}