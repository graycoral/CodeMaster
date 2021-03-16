#include <iostream>
#include <cstring>

#define MAXN	(2*100000 + 1)

using namespace std;

int input[MAXN];
int lArray[MAXN];
int hArray[MAXN];
int N;
void GetData()
{
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> input[i];
	}
}

int check(int* arr)
{
	int prevNum = arr[0];
	for (int i = 1; i < N; i++) {
		if (prevNum > arr[i])	return 1;
		prevNum = arr[i];
	}

	return 0;
}

void sort(int test_case)
{
	int i, j;
	int sortArray[MAXN] = {0};
	int ans = 0;

	memcpy(sortArray, input, sizeof(input));

	while (check(sortArray)) {
		memset(lArray, 0, sizeof(int) * N);
		memset(hArray, 0, sizeof(int) * N);

		for (i = N - 1; i >= 0; i--) {
			int last_num = sortArray[i];
			for (j = i - 1; j >= 0; j--) {
				if (last_num < sortArray[j]) {
					lArray[i] = last_num;
					break;
				}
			}
			if (j == -1)	hArray[i] = last_num;
		}

		// low
		int sortedIdx = 0;
		for (int idx = 0; idx < N; idx++) {
			if (lArray[idx] != 0) {
				sortArray[sortedIdx++] = lArray[idx];
			}
		}
		// high		
		for (int idx = 0; idx < N; idx++) {
			if (hArray[idx] != 0) {
				sortArray[sortedIdx++] = hArray[idx];
			}
		}
		ans++;
	}

	cout << "#" << test_case << " " <<ans << endl;
	
}


int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
	int test_case;
	int T;

	freopen("9712_input.txt", "r", stdin);
	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		GetData();
		sort(test_case);
	}
	return 0;
}