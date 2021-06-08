#include <iostream>
#include <iomanip>

using namespace std;

#define SWAP(a, b) {int t = a; a=b; b=t;}

void qSort(int* arr, int start, int end)
{
	if (start >= end)	return;
	int pivot = start;
	int i = start + 1; int j = end;
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
	qSort(arr, start, j - 1);
	qSort(arr, j + 1, end);
}

int main()
{
	int arr[10] = { 9,2,4,1,4,5,19, 20, 33, 18};

	for (int i = 0; i < 10; i++) {
		cout << setw(3) << arr[i];
	}
	cout << endl;
	qSort(arr, 0, 9);

	for (int i = 0; i < 10; i++) {
		cout << setw(3) << arr[i];
	}
	cout << endl;

	return 0;
}