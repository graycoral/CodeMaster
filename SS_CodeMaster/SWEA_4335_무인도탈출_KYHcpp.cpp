#include <iostream>

using namespace std;

#define MAX(a,b) (((a) > (b)) ? (a):(b))

typedef struct SQ {
	int l, r, h;
};

const int max_num = 20 + 1;
SQ sq[max_num];
SQ dp[max_num];
int visitied[max_num];
int max_height;
int N;

void input()
{
	for (int i = 0; i < N; i++) {
		sq[i].l = sq[i].r = sq[i].h = 0;
	}
	
	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> sq[i].l >> sq[i].r >> sq[i].h;
	}

	max_height = 0;
}

void DFS(int start, int left, int right, int height)
{
	int  i;
	if (start > N) {
		for (int i = 0; i < N; i++) {
			if (visitied[i] == 1)	cout << i << " ";
		}
		cout << endl;
		return;
	}

	max_height = MAX(max_height, height);
	for (i = start; i < N; i++) {
		if (visitied[i] == 1)	continue;
		visitied[i] = 1;
		if ((left >= sq[i].l && right >= sq[i].r)  || 
			(left >= sq[i].r && right >= sq[i].l)) {
			DFS(i +1, sq[i].l, sq[i].r, height + sq[i].h);
		}

		if ((left >= sq[i].r && right >= sq[i].h) ||
			(left >= sq[i].h && right >= sq[i].r)){
			DFS(i + 1, sq[i].r, sq[i].h, height + sq[i].l);
		}

		if ((left >= sq[i].h && right >= sq[i].l) ||
			(left >= sq[i].l && right >= sq[i].h)) {
			DFS(i + 1, sq[i].h, sq[i].l, height + sq[i].r);
		}
		visitied[i] = 0;
	}
	if ((left >= sq[i].l && right >= sq[i].r) ||
		(left >= sq[i].r && right >= sq[i].l)) {
		DFS(i + 1, sq[i].l, sq[i].r, height + sq[i].h);
	}

	if ((left >= sq[i].r && right >= sq[i].h) ||
		(left >= sq[i].h && right >= sq[i].r)) {
		DFS(i + 1, sq[i].r, sq[i].h, height + sq[i].l);
	}

	if ((left >= sq[i].h && right >= sq[i].l) ||
		(left >= sq[i].l && right >= sq[i].h)) {
		DFS(i + 1, sq[i].h, sq[i].l, height + sq[i].r);
	}
}

void DFS_TEST(int start)
{
	int i;
	if (start >= N) {
		for (int i = 0; i < N; i++) {
			if (visitied[i] == 1)	cout << i << " ";
		}
		cout << endl;
		return;
	}
	
	for (i = start; i < N; i++) {
		visitied[i] = 1;
		DFS_TEST(i+1);
		visitied[i] = 0;
	}
	DFS_TEST(i + 1);
}

void powerset(int idx, int depth)
{
	if (idx == depth) {
		int i;
		printf("{");
		for (i = 0; i < N; i++) {
			if (visitied[i] == 1)printf("%d ", visitied[i]);
		}
		printf("}\n");
		return;
	}

	visitied[depth] = 1;
	powerset(idx, depth + 1);
	visitied[depth] = 0;
	powerset(idx, depth + 1);
}

int sol()
{
	int retMaxNum = 0;
	SQ dp[max_num];

	for (int i = 0; i < N; i++) {
		dp[i].r = dp[i].l = dp[i].h = 0;
	}
	
	dp[0].h = sq[0].h;	dp[0].r = sq[0].r; dp[0].l = sq[0].l;
	for (int i = 1; i < N; i++) {
		for (int j = 0; j < i; j++) {
			int rMax = 0; int lMax = 0; int hMax = 0;
			int rR, lR, hR; int rL, lL, hL; int rH, lH, hH;
			
			if ((sq[j].r >= sq[i].r && sq[j].l >= sq[i].l) ||
				(sq[j].r >= sq[i].l && sq[j].l >= sq[i].r)) {
				rMax = MAX(dp[j].h + sq[i].h, dp[i].h);
			}

			if ((sq[j].r >= sq[i].r && sq[j].l >= sq[i].l) ||
				(sq[j].r >= sq[i].l && sq[j].l >= sq[i].r)) {
				lMax = MAX(dp[j].h + sq[i].h, dp[i].h);
			}

			if ((sq[j].r >= sq[i].r && sq[j].l >= sq[i].l) ||
				(sq[j].r >= sq[i].l && sq[j].l >= sq[i].r)) {
				hMax = MAX(dp[j].h + sq[i].h, dp[i].h);
			}

			dp[i].h = MAX(MAX(rMax, lMax), hMax);
		}
	}

	for (int i = 0; i < N; i++) {
		retMaxNum = MAX(retMaxNum, dp[i].h);
	}

	return retMaxNum;
}

int main()
{
	int test_case = 1;
	freopen("swea_4335_input.txt", "r", stdin);
	
	cin >> test_case;
	for (int i = 1; i <= test_case; i++) {
		input();
		//DFS(0, 10000, 10000, 0);
		//DFS_TEST(0);
		//cout << "===============" << endl;
		//cout << "#" << i << " " << max_height << endl;
		cout << sol() << endl;
		
	}
	return 0;
}