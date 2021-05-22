#include <iostream>
#include <iomanip>

using namespace std;

int n = 10;
int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
int v[10];

int main()
{
	for (int i = 0; i < (1 << n); i++) {
		for (int j = 0; j < n; j++) {
			if (i & (1 << j)) {
				cout << setw(3) << arr[j];
			}
		}
		cout << endl;
	}

	cout << endl;

	return 0;
}