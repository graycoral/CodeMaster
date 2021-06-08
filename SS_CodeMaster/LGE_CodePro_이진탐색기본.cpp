#include <iostream>

using namespace std;
const int max_num = 5e4 + 10;
int T, N;
int arr[max_num];


int sol()
{
	cin >> T;
	for (int i = 0; i < T; i++) {
		int tmp;
		cin >> tmp;
		arr[tmp] = i;
	}
	cin >> N;
	for (int i = 0; i < N; i++) {
		int tmp;
		cin >> tmp;
		cout << arr[tmp] << " ";
	}
	return 0;
}



int main()
{
	return 0;
}