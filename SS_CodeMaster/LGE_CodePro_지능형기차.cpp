#include <iostream>

using namespace std;

int in[4];
int out[4];
int sol;

#define MAX(a, b) (a > b ? a : b)
int main(void)
{
	int i;

	// 입력받는 부분
	for (i = 0; i < 4; i++)
	{
		cin >> out[i] >> in[i];
	}

	// 여기서부터 작성
	int inPeople = 0;
	for (int i = 0; i < 4; i++) {
		inPeople += (in[i] - out[i]);
		sol = MAX(sol, inPeople);
	}

	// 출력하는 부분
	cout << sol << endl;

	return 0;
}