#include <iostream>

using namespace std;

#define MAX(a,b) (a>b? a:b)

const int max_num = 20 + 1;
int map[max_num][max_num];
int N;

void input()
{
	cin >> N;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			cin >> map[r][c];
		}
	}
}

#define DEBUG (1)
#include <iomanip>
void show()
{
#if DEBUG
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			cout << setw(3) << map[r][c];
		}
	}
#endif

}

int getMaxBlock()
{
	int retVal = 0;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			retVal = MAX(retVal, map[r][c]);
		}
	}

	return retVal;
}

void reOrder(int d)
{
	int tmpArr[max_num];

	for (int i = 0; i < N; i++) {
		int tmpIdx = 0;
		for (int j = 0; j < N; j++) {
			// UP  || Down
			if ((d == 0) || (d == 1)) {
				if (map[j][i] == 0)	continue;
				tmpArr[tmpIdx++] = map[j][i];
			}
			// LEFT || RIGHT
			else if ((d == 2) || (d == 3)) {
				if (map[i][j] == 0)	continue;
				tmpArr[tmpIdx++] = map[i][j];
			}
		}

		for (int j = 0; j < tmpIdx; j++) {
			// UP
			if (d == 0) {
				map[j][i] = tmpArr[tmpIdx++];
			}
			// DOWN
			else if (d == 1) {
				map[tmpIdx - j - 1][i] = tmpArr[tmpIdx++ - j -1];
			}
			// LEFT
			else if (d == 2) {
				map[i][j] = tmpArr[tmpIdx++];
			}
			// Right
			else if (d == 3) {
				map[i][tmpIdx - j - 1] = tmpArr[tmpIdx++ - j - 1];
			}
		}
	}
}

int Move(int d, int cnt)
{
	int retVal = 0;
	if (cnt > 0)	return getMaxBlock();

	reOrder(d);
	//copy to tmpArry
	for (int i = 0; i < 4; i++) {
		int tmp[max_num][max_num];
		for (int r = 0; r < N; r++) {
			for (int c = 0; c < N; c++) {
				tmp[r][c] = map[r][c];
			}
		}

		retVal = MAX(retVal, Move(i, cnt - 1));
		
		for (int r = 0; r < N; r++) {
			for (int c = 0; c < N; c++) {
				map[r][c] = tmp[r][c];
			}
		}
	}
}

int main()
{
	input();
	cout << Move(0, 5) << endl;
	return 0;
}