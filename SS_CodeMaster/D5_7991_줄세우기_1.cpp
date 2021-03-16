#include <iostream>
#include <cstring>

#define SWAP(a,b) {int t = a; a=b; b=t;}
using namespace std;

int input[5000 + 1];
int N;

void qsort(int* arr, int start, int end)
{
	if (start >= end)	return;

	int pivot = start;
	int i = pivot + 1;
	int j = end;

	while (i <= j) {
		while (i <= end && arr[i] <= arr[pivot]) {
			++i;
		}
		while (j > start&& arr[j] >= arr[pivot]) {
			--j;
		}
		if (i >= j)	break;

		SWAP(arr[i], arr[j]);
	}
	SWAP(arr[j], arr[pivot]);

	qsort(arr, start, j - 1);
	qsort(arr, j + 1, end);
}

void show(int test_case)
{
	cout << "#" << test_case << " ";
	for (int i = 0; i < N; i++) {
		cout << input[i] << " ";
	}
	cout << endl;
}

void ReadData()
{
	memset(input, 0, sizeof(input));

	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> input[i];
	}
	qsort(input, 0, N - 1);
}

int check()
{
	for (int i = 0; i < N - 1; i++) {
		if (input[i] + 1 == input[i + 1])	return i + 1;
	}
	// -1 is ok
	return -1;
}

int findR(int idx)
{
	int minVal = 0xffff;
	int retIdx = -1;

	for (int i = idx + 1; i < N; ++i)
	{
		if (input[i] < minVal && input[idx] < input[i]) {
			minVal = input[i];
			retIdx = i;
		}
	}

	return retIdx;
}

int findL(int idx)
{
	int maxVal = input[idx - 1];
	int retIdx = idx - 1;

	for (int i = idx - 1; i >= 0; --i)
	{
		if (input[i] == maxVal) {
			maxVal = input[i];
			retIdx = i;
		}
		else break;
	}

	return retIdx;
}

void sol(int tc)
{
	while (1) {
		int checkVal = check();

		if (checkVal == -1) {
			show(tc);
			return;
		}
		else {
			int change_Idx = findR(checkVal);
			if (change_Idx == -1) {
				change_Idx = findL(checkVal);
			}

			SWAP(input[checkVal], input[change_Idx]);
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int test_case;
	int T;
	//freopen("7991_imput.txt", "r", stdin);
	cin >> T;
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/
	for (test_case = 1; test_case <= T; ++test_case)
	{
		ReadData();
		sol(test_case);
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}