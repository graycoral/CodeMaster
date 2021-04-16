#include <iostream>

using namespace std;

const int maxn = 10 + 1;

typedef struct AP {
	int r, c;
	int coverage;
	int perfomance;
} AP;

int map[maxn][maxn];

int moveA[100 + 1];
int moveB[100 + 1];

int M, A;

int dr[] = { 0, -1, 0, 1, 0 };
int dc[] = { 0, 0, 1, 0, -1 };

AP ap[10];

void init()
{	
	for (int i = 0; i < maxn; i++) {
		for (int j = 0; j < maxn; j++) {
			map[i][j] = 0;
		}
	}
	for (int i = 0; i <= M; i++) {
		moveA[i] = moveB[i] =0;
	}
}

void input()
{
	cin >> M >> A;
	for (int i = 1; i <= M; i++) {		
		cin >> moveA[i];
	}
	for (int i = 1; i <= M; i++) {
		cin >> moveB[i];
	}
	for (int i = 1; i <= A; i++) {
		cin >> ap[i].c >> ap[i].r >> ap[i].coverage >> ap[i].perfomance;
	}
}

int getMaxAp(int r, int c)
{
	int retApIdx = 0;
	int maxPerformmance = 0;

	for (int i = 1; i <= A; i++) {
		int distX = ap[i].c - c > 0 ? ap[i].c - c : (ap[i].c- c) * -1;
		int distY = ap[i].r - r > 0 ? ap[i].r - r : (ap[i].r - r) * -1;
		 
		if (distX + distY <= ap[i].coverage && ap[i].perfomance > maxPerformmance) {
			retApIdx = i;
			maxPerformmance = ap[i].perfomance;
		}
	}
	return retApIdx;
}

void getDupltedIdx(int sr, int sc, int er, int ec, int* apAIdx, int* apBIdx)
{	
	int maxPerformmance = 0;
	for (int i = 1; i <= A; i++) {
		int distX = ap[i].c - sc > 0 ? ap[i].c - sc : (ap[i].c - sc) * -1;
		int distY = ap[i].r - sr > 0 ? ap[i].r - sr : (ap[i].r - sr) * -1;

		if (distX + distY <= ap[i].coverage) {			
			for (int j = 1; j <= A; j++) {
				int distEndX = ap[j].c - ec > 0 ? ap[j].c - ec : (ap[j].c - ec) * -1;
				int distEndY = ap[j].r - er > 0 ? ap[j].r - er : (ap[j].r - er) * -1;

				if (distEndX + distEndY <= ap[j].coverage) {
					int tmpSumPerformmance = 0;
					if (i == j)	tmpSumPerformmance = ap[i].perfomance;
					else		tmpSumPerformmance = ap[i].perfomance + ap[j].perfomance;

					if (tmpSumPerformmance > maxPerformmance) {
						maxPerformmance = tmpSumPerformmance;
						*apAIdx = i;
						*apBIdx = j;
					}
				}
			}
		}
	}
}

void sol(int test_case)
{
	int startR = 1; int startC = 1;
	int endR = 10; int endC = 10;
	int sumA = 0; int sumB = 0;

	for (int i = 0; i <= M; i++) {		
		startR += dr[moveA[i]];
		startC += dc[moveA[i]];
		
		endR += dr[moveB[i]];
		endC += dc[moveB[i]];

		int apAIdx = getMaxAp(startR, startC);
		int apBIdx = getMaxAp(endR, endC);

		if (apAIdx == apBIdx && apAIdx != 0) {
			getDupltedIdx(startR, startC, endR, endC, &apAIdx, &apBIdx);			
		}

		if (apAIdx == apBIdx && apAIdx != 0) {
			sumA += (ap[apAIdx].perfomance / 2);
			sumB += (ap[apBIdx].perfomance / 2);
		}
		else {
			sumA += ap[apAIdx].perfomance;
			sumB += ap[apBIdx].perfomance;
		}
	}

	cout << "#" << test_case+1 << " " << sumA + sumB << endl;
}

int main()
{
	int test_case;
	//freopen("모의고사_5644_무선충전.txt", "r", stdin);
	cin >> test_case;

	for (int i = 0; i < test_case; i++) {		
		input();
		sol(i);
		init();
	}
	return 0;
}