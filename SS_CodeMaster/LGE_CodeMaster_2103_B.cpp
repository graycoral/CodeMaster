#include <iostream>

using namespace std;

const long long int maxn = 20;

int num[maxn];
int num1[maxn];
int num2[maxn];

int len;
int numLen = 0;

#define SWAP(a, b) {int t = b; b=a; a=t;}

void init()
{
	for (int i = 0; i < maxn; ++i) {
		num[i] = -1; num1[i] = -1; num2[i] = -1;

	}
	len = 0;
	numLen = 1;
	
}

void qsort_int(int* arr, int start, int end)
{
	if (start >= end)	return;

	int pivot = start;
	int i = start + 1;
	int j = end;

	while (i <= j) {
		while (arr[i] >= arr[pivot]) {
			++i; break;
		}
		while (arr[j] < arr[pivot]) {
			--j; break;
		}
		if (i > j)	break;
		SWAP(arr[i], arr[j]);
	}
	SWAP(arr[j], arr[pivot]);

	qsort_int(arr, start, j - 1);
	qsort_int(arr, j+1, end);
}

void input()
{
	string tmp;
	cin >> tmp;

	len = tmp.size();
	for (int i = 0; i < len; ++i) {
		if (tmp[i] == '6') tmp[i] = '9';
		num[i] = static_cast<char>(tmp[i]) - '0';
	}
	qsort_int(num, 0, len);
}

long long int getNum(int* arr)
{
	long long int retNum = 0;
	int x = 1;
	
	for (int i = 1; i < len; i++) {
		if (arr[i] == -1)	break;
		x *= 10;
	}

	for (int i = 0; i < len; i++) {
		if (arr[i] == -1)	break;
		retNum += (arr[i] * x);
		x /= 10;
	}

	return retNum;
}

void sol()
{
	int numIdx = 0;
	int num1Idx = 0;
	int num2Idx = 0;

	num1[num1Idx++] = num[numIdx++];
	num2[num2Idx++] = num[numIdx++];

	while (numIdx < len) {
		if (getNum(num1) > getNum(num2)) {
			num2[num2Idx++] = num[numIdx++];
		}
		else {
			num1[num1Idx++] = num[numIdx++];
		}
	}
}

int main()
{
	int t;
	//freopen("LGE_CodeMaster_2013_B.txt", "r", stdin);
	cin >> t;

	for (int i = 0; i < t; ++i) {
		init();
		input();
		sol();

		cout << getNum(num1) * getNum(num2) << endl;
	}

	return 0;
}