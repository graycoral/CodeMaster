#include <iostream>
#include <memory.h>
#include <algorithm>

using namespace std;

int N;
int input[1000];
int arr[5005];

int comp(void const* a, void const* b) {
	int x = *(int*)a;
	int y = *(int*)b;
	if (x > y)
		return 1;
	else if (x < y)
		return -1;
	else
		return 0;

}
int main(int argc, char** argv)
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int test_case;
	int T;

	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		int input_value;
		int index = 0;
		int max_val = 0;
		cin >> N;

		memset(arr, 0x00, sizeof(arr));
		memset(input, 0x00, sizeof(input));
		for (int i = 0; i < N; i++) {
			cin >> input_value;
			input[input_value]++;
			max_val = input_value;
		}

		for (int i = 1; i < max_val; i++) {

			if (i == max_val - 1) {
				int tmp = index;
				if (input[max_val] > 0) {
					while (index < input[max_val] + tmp) {
						arr[index] = max_val; //10                      
						index++;
					}
				}
				tmp = index;
				while (index < input[i] + tmp) {
					arr[index] = i; //9                     
					index++;
				}

			}
			else if (input[i] > 0) {

				int tmp = index;
				while (index < input[i] + tmp) {
					arr[index] = i;
					index++;
					//Sleep(1000);
				}
				input[i] = 0;

				for (int j = i + 2; j <= 10; j++) {
					if (input[j] > 0) {
						arr[index++] = j;
						input[j]--;
						break;
					}
				}
			}

		}
		cout << "#" << test_case;
		for (int i = 0; i < N; i++) {
			cout << " " << arr[i];
		}
		cout << endl;
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}