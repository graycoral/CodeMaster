#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN ((int)1e5)
#define SWAP(a, b) {DATA t = a; a = b; b= t;}
#define MAX(a, b) (a > b ? a : b)
int N;//영화수
struct DATA {
	int s, e;//시작시간, 종료시간
};
DATA A[MAXN + 10];

void qsort(DATA* arr, int start, int end)
{
	if (start >= end)	return;

	int pivot = start;
	int i = start + 1;
	int j = end;
	while (i < j) {
		while (arr[i].s <= arr[pivot].s) {
			++i;
		}
		while (arr[j].s > arr[pivot].s) {
			--j;
		}
		if (i >= j)	break;
		SWAP(arr[i], arr[j]);
	}
	SWAP(arr[j], arr[pivot]);
	qsort(arr, start, j - 1);
	qsort(arr, j + 1, end);
}

void InputData() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> A[i].s >> A[i].e;
	}
	qsort(A, 0, N-1);
	//sort(A, A + N - 1);
}

int sol()
{
	int tmpCnt = 1;
	int ans = 0;
	for (int c = 1; c < N; c++) {
		int preEnd = A[c-1].e;
		for (int i = c + 1; i < N; i++) {
			if (preEnd < A[i].s) {
				tmpCnt++;
				preEnd = A[i].e;
			}
		}
		ans = MAX(ans, tmpCnt);
		tmpCnt = 1;
	}

	return ans;
}


int main() {
	InputData();//입력

	//여기서부터 작성

	cout << sol() << endl;//출력
	return 0;
}