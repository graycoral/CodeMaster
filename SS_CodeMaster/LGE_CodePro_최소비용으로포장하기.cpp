#include <iostream>

using namespace std;

#define SWAP(a, b) {int t = a; a = b; b= t;}

const int max_num = 50001;
int pack[max_num];
int N;

void sort(int* arr, int start, int end)
{
	if (start >= end)	return;
	int pivot = start;
	int i = start + 1;
	int j = end;

	while (i <= j) {
		while (arr[pivot] <= arr[i]) {
			++i;
		}
		while (arr[j] <= arr[end]) {
			--j;
		}
		if (i > j)	break;
		SWAP(arr[i], arr[j]);
	}
	SWAP(arr[j], arr[pivot]);
	sort(arr, start, j - 1);
	sort(arr, j + 1, end);
}

void input()
{
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> pack[i];
	}
}

void sol()
{
	int ans = 0;
	for (int i = 0; i < N; i++) {
		sort(pack, i, N);
		pack[i + 1] += pack[i];
	
		ans += pack[i + 1];
	}
}

int main()
{
	return 0;
}
