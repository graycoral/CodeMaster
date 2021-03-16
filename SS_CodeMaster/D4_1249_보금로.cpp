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
#include<cstdio>
#include<queue>

using namespace std;

int qsize = 0;
int nsize = 0;

struct pos {
	int r, c;
};

int visited[100 + 1][100 + 1];
int navi[100 + 1][100 + 1];

int dr[] = { 1,-1, 0, 0 };
int dc[] = { 0,0, 1, -1 };

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	int test_case;
	int T;

	//FILE* fFile = freopen("1249_input.txt", "r", stdin);	
	cin >> T;	
	/*
	   ���� ���� �׽�Ʈ ���̽��� �־����Ƿ�, ������ ó���մϴ�.
	*/
	for (test_case = 1; test_case <= T; ++test_case)
	{		
		
		queue <pair<int, int >> q;
		cin >> nsize;		

		for (int i = 0; i < nsize; i++) {
			char tmp[101] = { 0, };
			cin >> tmp;
			for (int j = 0; j < nsize; j++) {				
				navi[i][j] = tmp[j] - '0';
				visited[i][j] = 0xffff;
			}
		}
		q.push({ 0, 0 });
		visited[0][0] = 0;

		while (!q.empty()) {			
			int tmpr = q.front().first;
			int tmpc = q.front().second;
			q.pop();
			
			for (int i = 0; i < 4; i++) {
				int nr = tmpr + dr[i];
				int nc = tmpc + dc[i];
				int nval = visited[tmpr][tmpc] + navi[nr][nc];

				if (nr >= nsize || nc >= nsize)	continue;
				if (nr < 0 || nc < 0)	continue;
				if (nval >= visited[nr][nc])	continue;
				
				q.push({ nr, nc });
				visited[nr][nc] = nval;
			}
		}

		cout << "#" << test_case << " " << visited[nsize - 1][nsize - 1] << endl;
	}
	return 0;//��������� �ݵ�� 0�� �����ؾ��մϴ�.
}