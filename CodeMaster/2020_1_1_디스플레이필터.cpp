#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 0xfffff;

int N;	// 필터의 수
int R[11]; // 반사의 정도
int P[11]; // 투과의 정도
int Diff = MAXN;
int Cnt = 0;

void InputData(void){
	cin >> N;
	for(int i=1; i<=N; i++)  {
		cin >> R[i] >> P[i];
	}
}

void DFS(int n, int r, int p, int cnt)
{
    if( n > N ) return;

    if( n != 0) {
        if( Diff > abs(r-p))    Diff = abs(r-p); Cnt = cnt;
    }

    DFS(n+1, r*R[n], p + P[n], cnt+1);
    DFS(n+1, r, p, cnt);
}

int main(){
	int ans = -1;
	InputData(); // 입력함수
    DFS(0, 1, 0, 0);
    ans = N - Cnt;
	// 코드를 작성 하세요
	cout << ans << endl;//출력
	return 0;
}


