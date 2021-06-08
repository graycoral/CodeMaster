#include <iostream>
#include <iomanip>

#define MAX(a,b) (a>b ? a : b)
using namespace std;

void show(int* arr, int size)
{
	for (int i = 0; i < size; i++) {
		cout << setw(3) << arr[i];
	}
	cout << endl;
}

const int max_num = 1000;
void countSort(int* arr, int size)
{
	int retArry[max_num];
	int count[max_num]; int countSum[max_num];

	//init
	for (int i = 0; i < max_num; i++) {
		count[i] = countSum[i] = retArry[i] = 0;
	}

	//count
	for (int i = 0; i < size; i++) {
		count[arr[i]]++;
	}

	//countSum
	countSum[0] = count[0];
	for (int i = 1; i < max_num; i++) {
		countSum[i] = countSum[i - 1] + count[i];
	}

	//order
	for (int i = size-1; i >= 0; i--) {
		retArry[countSum[arr[i]] -1] = arr[i];
		countSum[arr[i]]--;
	}

	//copy
	for (int i = 0; i < size; i++) {
		arr[i] = retArry[i];
	}
}

int main()
{
	int* retArr;
	int arr[20] = { 9,7,6, 4,19,1, 1,1,5, 4, 99, 20, 20, 60, 32, 9, 34, 33, 5, 67 };
	show(arr, 20);
	countSort(arr, 20);
	show(arr, 20);
	return 0;
}