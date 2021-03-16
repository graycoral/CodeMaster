#include <iostream>
#include <iomanip>

#define SWAP(a , b)	{int t; t=a; a=b; b=t;}
using namespace std;

//int pData[10] = {4,1,2,4,9,7,8,6,10,5};
int pData[] = { 3, 8, 2, 1, 2, 4, 2, 3, 4, 5 };

void qsort(int* arr, int start, int end)
{
	if (start >= end) return;

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

		SWAP(arr[i], arr[j]);
	}

	SWAP(arr[j], arr[pivot]);

	qsort(arr, start, j - 1);
	qsort(arr, j+1, end);

	
}

int main()
{
	cout << "BEFORE" << endl;
	for (int i = 0; i < 10; i++) {
		cout << pData[i] << setw(3);
	}
	qsort(pData, 0, 9);
	//qsort_ori(pData, 0, 9);

	cout << endl << "AFTER" << endl;
	for (int i = 0; i < 10; i++) {
		cout << pData[i] << setw(3);
	}
}

