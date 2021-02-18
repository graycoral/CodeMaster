/////////////////////////////////////////////////////////////////////////////////////////////
// �⺻ �����ڵ�� ���� �����ص� ���� �����ϴ�. ��, ����� ���� ����
// �Ʒ� ǥ�� ����� ���� �ʿ�� �����ϼ���.
// ǥ�� �Է� ����
// int a;
// float b, c;
// double d, e, f;
// char g;
// char var[256];
// long long AB;
// cin >> a;                            // int ���� 1�� �Է¹޴� ����
// cin >> b >> c;                       // float ���� 2�� �Է¹޴� ���� 
// cin >> d >> e >> f;                  // double ���� 3�� �Է¹޴� ����
// cin >> g;                            // char ���� 1�� �Է¹޴� ����
// cin >> var;                          // ���ڿ� 1�� �Է¹޴� ����
// cin >> AB;                           // long long ���� 1�� �Է¹޴� ����
/////////////////////////////////////////////////////////////////////////////////////////////
// ǥ�� ��� ����
// int a = 0;                            
// float b = 1.0, c = 2.0;               
// double d = 3.0, e = 0.0; f = 1.0;
// char g = 'b';
// char var[256] = "ABCDEFG";
// long long AB = 12345678901234567L;
// cout << a;                           // int ���� 1�� ����ϴ� ����
// cout << b << " " << c;               // float ���� 2�� ����ϴ� ����
// cout << d << " " << e << " " << f;   // double ���� 3�� ����ϴ� ����
// cout << g;                           // char ���� 1�� ����ϴ� ����
// cout << var;                         // ���ڿ� 1�� ����ϴ� ����
// cout << AB;                          // long long ���� 1�� ����ϴ� ����
/////////////////////////////////////////////////////////////////////////////////////////////

#include<iostream>

using namespace std;

int levels[10000];
int navi[301][301];
int numr[10000];
int numc[10000];
int dc[6] = { 1,2,1,-1,-2,-1 };
int dr[6] = { -1,0,1,1,0,-1 };
int front;
int rear;
int visitied[10000];

int CheckLevel(int num)
{
	for (int i = 1; i < 10000; i++) {
		if (levels[i] > num) return i-1;
	}

	return 0xffff;
}

struct pos {
	int r, c;
	int val;
};

struct pos q[1000];


void push(int r, int c, int val)
{
	q[rear].r = r;
	q[rear].c = c;
	q[rear++].val = val;
}

bool empty()
{
	return front == rear ? true : false;
}

struct pos pop()
{
	return q[rear--];
}

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int test_case;
	int T;
	/*
	   �Ʒ��� freopen �Լ��� input.txt �� read only �������� �� ��,
	   ������ ǥ�� �Է�(Ű����) ��� input.txt ���Ϸκ��� �о���ڴٴ� �ǹ��� �ڵ��Դϴ�.
	   //�������� �ۼ��� �ڵ带 �׽�Ʈ �� ��, ���Ǹ� ���ؼ� input.txt�� �Է��� ������ ��,
	   freopen �Լ��� �̿��ϸ� ���� cin �� ������ �� ǥ�� �Է� ��� ���Ϸκ��� �Է��� �޾ƿ� �� �ֽ��ϴ�.
	   ���� �׽�Ʈ�� ������ ������ �Ʒ� �ּ��� ����� �� �Լ��� ����ϼŵ� �����ϴ�.
	   freopen �Լ��� ����ϱ� ���ؼ��� #include <cstdio>, Ȥ�� #include <stdio.h> �� �ʿ��մϴ�.
	   ��, ä���� ���� �ڵ带 �����Ͻ� ������ �ݵ�� freopen �Լ��� ����ų� �ּ� ó�� �ϼž� �մϴ�.
	*/
	freopen("4112_input.txt", "r", stdin);
	cin >> T;
	/*
	   ���� ���� �׽�Ʈ ���̽��� �־����Ƿ�, ������ ó���մϴ�.
	*/	

#if 0
	for (int i = 1; i < 10000; i++) {
		if (levels[i - 1] >= 10000) break;
		levels[i] = levels[i - 1] + i;
	}
#endif

	int num = 1;
	while (num <= 10000) {
		for (int i = 1; i <= 300; i++) {
			for (int j = 150 - i; j < 150 + i; j += 2) {
				numr[num] = i;
				numc[num] = j;
				navi[i][j] = num++;
			}
		}
	}
	
	for (test_case = 1; test_case <= T; ++test_case)
	{
		int start, end;
		cin >> start >> end;
		push(numr[start], numc[start], 0);

		while (!empty()) {
			struct pos tmp = pop();
			
			if (navi[tmp.r][tmp.c] == end)
			{
				cout << "#" << test_case << " " << tmp.val << endl;
				break;
			}
			for (int i = 0; i < 6; i++) {
				int nr = tmp.r + dr[i];
				int nc = tmp.c + dc[i];
				int nval = tmp.val + 1;

				if (nr <= 0 || nc <= 0 || nr > 300 || nc > 300 || navi[nr][nc] == 0 || visitied[navi[nr][nc]] > 0) continue;
				push(nr, nc, nval);
				visitied[navi[nr][nc]]++;
			}
		}
	}
	return 0;//��������� �ݵ�� 0�� �����ؾ��մϴ�.
}