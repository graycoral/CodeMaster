#include <iostream>
#include <algorithm>
#define MAXN	((int)1e4+10)

using namespace std;

int N;//���� ��
int S;//���� ���� ��ȣ
int M;
int v[MAXN];
int q[MAXN];
int wp, rp;

void InputData() {
	cin >> N >> S >> M;
}

int pop() { return q[rp++]; }
int empty() { return wp == rp; }

void push(int s)
{
	int idx = s, newIdx = 0;
	int cnt = -1, i = 0;
	idx %= N;

	while (M - cnt) {
		if (v[(idx + i)%N] == 0)	cnt++;
		newIdx = (idx + i) % N;
		i++;
	}

	v[newIdx] = 1;
	q[wp++] = newIdx;
	cout << newIdx << " ";
}

void sol()
{
	int num = N - 1;
	push(S);
	while (!empty()) {
		int cur = pop();
		push(cur);
	}
}

void PRT() 
{
	for (int i = 1; i <= N; i++)	cout << q[i];
}

int main() {

	InputData();//	�Է� �Լ�

	//	�ڵ带 �ۼ��ϼ���
	sol();
	//PRT();

	return 0;
}