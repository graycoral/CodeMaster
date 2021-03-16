/////////////////////////////////////////////////////////////////////////////////////////////
// 기본 제공코드는 임의 수정해도 관계 없습니다. 단, 입출력 포맷 주의
// 아래 표준 입출력 예제 필요시 참고하세요.
// 표준 입력 예제
// int a;
// float b, c;
// double d, e, f;
// char g;
// char var[256];
// long long AB;
// cin >> a;                            // int 변수 1개 입력받는 예제
// cin >> b >> c;                       // float 변수 2개 입력받는 예제 
// cin >> d >> e >> f;                  // double 변수 3개 입력받는 예제
// cin >> g;                            // char 변수 1개 입력받는 예제
// cin >> var;                          // 문자열 1개 입력받는 예제
// cin >> AB;                           // long long 변수 1개 입력받는 예제
/////////////////////////////////////////////////////////////////////////////////////////////
// 표준 출력 예제
// int a = 0;                            
// float b = 1.0, c = 2.0;               
// double d = 3.0, e = 0.0; f = 1.0;
// char g = 'b';
// char var[256] = "ABCDEFG";
// long long AB = 12345678901234567L;
// cout << a;                           // int 변수 1개 출력하는 예제
// cout << b << " " << c;               // float 변수 2개 출력하는 예제
// cout << d << " " << e << " " << f;   // double 변수 3개 출력하는 예제
// cout << g;                           // char 변수 1개 출력하는 예제
// cout << var;                         // 문자열 1개 출력하는 예제
// cout << AB;                          // long long 변수 1개 출력하는 예제
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
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
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
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}