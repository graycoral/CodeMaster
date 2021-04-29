#include <iostream>
#include <algorithm>

using namespace std;

typedef struct nutruo {
	int p; //단백질
	int f; //지방
	int s; // 탄수화물
	int v; // 비타민
	int c; // 비용
	int idx;
} Nutro;

Nutro food[16];
Nutro selFood[16];

#define SWAP_NUTRO(a,b) { Nutro t = a; a =b; b=t;}
#define SWAP_INT(a,b) { int t = a; a =b; b=t;}
#define MAX(a,b ) (a > b ? a :b)
#define MIN(a,b ) (a < b ? a :b)


int pi, fi, si, vi;
int N;
int totalSum = 0xfffe;
int totalIdx = 0;
int idxArr[16];
int tmpArr[16];
int visited[10];

void qsort(Nutro* arr, int start, int end)
{
	if (start >= end)	return;
	int pivot = start;
	int i = pivot + 1;
	int j = end;

	while (i<=j) {
		while (i <= end && arr[i].c <= arr[pivot].c) {
			++i;
		}
		while (j > start && arr[j].c >= arr[pivot].c) {
			--j;
		}
		if (i >= j)	break;
		SWAP_NUTRO(arr[i], arr[j]);
	}
	SWAP_NUTRO(arr[j], arr[pivot]);

	qsort(arr, start, j - 1);
	qsort(arr, j + 1, end);
}

void qsort_int(int* arr, int start, int end)
{
	if (start > end)	return;
	int pivot = start;
	int i = pivot + 1;
	int j = end;

	while (i <= j) {
		while (i <= end && arr[i] <= arr[pivot]) {
			++i;
		}
		while (j > start && arr[j] >= arr[pivot]) {
			--j;
		}
		if (i >= j)	break;
		SWAP_INT(arr[i], arr[j]);
	}
	SWAP_INT(arr[j], arr[pivot]);

	qsort_int(arr, start, j - 1);
	qsort_int(arr, j + 1, end);
}


void input()
{
	//freopen("BAEKJOON_19942_다이어트.txt", "r", stdin);
	cin >> N;

	cin >> pi >> fi >> si >> vi;
	for (int i = 0; i < N; i++) {
		cin >> food[i].p >> food[i].f >> food[i].s >> food[i].v >> food[i].c;
		food[i].idx = i;
		tmpArr[i] = idxArr[i] = 0xfffe;
	}
	//qsort(food, 0, N-1);
}

int CheckSort(int* arr1, int* arr2)
{	
	int idx = 0;
	if (totalIdx == 0)	return 1;
	while (arr1[idx] != 0xfffe || arr2[idx] != 0xfffe) {
		if (arr1[idx] > arr2[idx])	 return 1;
		idx++;
	}

	return 0;
}

void sol(int idx, int s, int sumP, int sumF, int sumS, int sumV, int sumC)
{
	if (sumC > totalSum)	return;	
	if (sumP >= pi && sumF >= fi && sumS >= si && sumV >= vi && totalSum > sumC) {
		if (totalSum == sumC && CheckSort(idxArr, tmpArr) == 0)	return;
		totalSum = sumC;
		for (int i = 0; i < idx; i++) {
			idxArr[i] = tmpArr[i];
		}
		qsort_int(idxArr, 0, idx-1);
		totalIdx = idx;
		return;
	}

	for (int i = s; i < N; i++) {
		if (visited[i] == 1)	continue;
		tmpArr[idx] = food[i].idx;
		visited[i] = 1;
		sol(idx + 1, i, \
			sumP + food[i].p, \
			sumF + food[i].f, \
			sumS + food[i].s, \
			sumV + food[i].v, \
			sumC + food[i].c);
		tmpArr[idx] = 0xfffe;
		visited[i] = 0;
	}
}

int main()
{
	input();

	sol(0, 0, 0, 0, 0, 0, 0);

	if (totalSum == 0xfffe)	cout << "-1" << endl;
	else {
		cout << totalSum << endl;
		for (int i = 0; i < totalIdx; i++) {
			if (idxArr[i] == 0xfffe)	continue;
			cout << idxArr[i] + 1 << " ";
		}
		cout << endl;
	}
	
	return 0;
}