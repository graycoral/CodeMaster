#include <iostream>
#include <algorithm>

using namespace std;

int N;//지도 크기
char map[110][110];//지도 정보
int cache[100][100];

// up, down, left, right
int dx[4] = { -1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

void init()
{
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			cache[i][j] = -1;
		}
	}
}

int dp(int x, int y, int price){
	
	for(int i=0; i<4; i++){
		int nx = x + dx[i];
		int ny = y + dy[i];
		
		if( 0<=nx && nx<N && 0<=ny && ny<N){
			if(cache[nx][ny]!=-1)
				dp(nx,ny,price);
		}
	}

	return ret = min(dp(x+1,y,price + map[x][y]-'0'), dp(x,y+1,price+map[x][y]-'0'));
}

void Input_Data(){
	cin >> N;
	for (int i = 0; i < N; i++){
		cin >> map[i];
	}
}

int main(){
	int ans = -1;
	Input_Data();		//	입력 함수
	
	//	코드를 작성하세요
	init();
	dp(0,0,0);
	
	cout << cache[N-1][N-1] << endl;	//	정답 출력
	return 0;
}
