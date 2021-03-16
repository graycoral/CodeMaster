#include<iostream>

using namespace std;

#define MAXN (501)
#define SWAP(a ,b) {int t = a; a =b; b= t;}

int input[MAXN];
double length[MAXN];
int max_num = 0;
int tCnt = 0;
int N;
double M;
double dr[] = {0,1 };
double dc[] = {1,0 };
int r = 0, c = 0;

struct tile {
	double r, c;
};

struct tile tileQ[MAXN];
int front, rear;

void push(int r, int c)
{
	struct tile tmp;
	tmp.r = r;
	tmp.c = c;
	tileQ[rear++] = tmp;
}

int size()
{
	return rear - front;
}

struct tile pop()
{
	return tileQ[front++];
}

void GetData()
{
	max_num = 0;
	tCnt = 0;
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		int tmp;
		cin >> tmp;
		input[tmp]++;
		tCnt++;
		if (max_num < tmp)	max_num = tmp;
	}
}

double getLength(int k)
{
	if (length[k] != 0)	return length[k];
	
	length[0] = 1;
	for (int i = 1; i <= max_num; i++) {
		length[i] = length[i-1] * 2;
	}

	return length[k];	
}

int visited[MAXN][MAXN];

void cal(int idx, int r, int c)
{
	if (r > M || c > M)	return;
	if (visited[r][c] == 1)	return;
	if (input[idx] == 0)	return;	

	visited[r][c] = 1;
	input[idx]--;
	tCnt--;

	for (int i = 0; i < 2; i++) {
		double len = getLength(idx);
		cal(idx, r+len*dr[i], c+len*dc[i]);
	}
}

void sol(int test_case)
{
	int ans = 0;
	while (tCnt) {
		for (int i = max_num; i >= 0; i--) {
			double len = getLength(input[i]);
			cal(i, len, len);
		}
		ans++;
	}
}

void cal_tile()
{

}



int main(int argc, char** argv)
{
	int test_case;
	int T;

	freopen("1812_input.txt", "r", stdin);
	cin >> T;
	
	for (test_case = 1; test_case <= T; ++test_case)
	{
		GetData();
		sol(test_case);		
	}
	return 0;
}