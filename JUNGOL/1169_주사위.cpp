#include <iostream>
#include <vector>

using namespace std;
int N, M;
int cache[1000];
int used[1000];
vector<int> Data;

void sol1(int s)
{
	if (s > N) {
		for (int i = 1; i <= N; i++) {
			cout << cache[i] << " ";
		}
		cout << endl;
		return;
	}
	for (int i = 1; i <= 6; i++) {
		cache[s] = i;
		sol1(s + 1);
	}
}

void sol2(int s, int n)
{
	if (s > N) {
		for (int i = 1; i <= N; i++) {
			cout << cache[i] << " ";
		}
		cout << endl;
		return;
	}
	for (int i = n; i <= 6; i++) {
		cache[s] = i;
		sol2(s + 1, i);
	}

}

void sol3(int s)
{
	if (s > N) {
		for (int i = 1; i <= N; i++) {
			cout << cache[i] << " ";
		}
		cout << endl;
		return;
	}
	for (int i = 1; i <= 6; i++) {
		if (used[i] == 1)	continue;
		used[i] = 1;
		cache[s] = i;
		sol3(s+1);
		used[i] = 0;
	}
}

void printPicked(vector<int>& picked)
{
    for(auto p : picked){
        cout << p << " ";
    }
    cout << endl;
}

void pick(int n, vector<int>& picked, int toPick)
{
    if(toPick == 0){
        printPicked(picked);
        return;
    }
    int smallest = picked.empty() ? 0 : picked.back() + 1;
    for(int next = smallest; next < n; next++){
        picked.push_back(next);
        pick(n, picked, toPick -1);
        picked.pop_back();
    }
}

int main()
{
	cin >> N >> M;
	if (M == 1) {
		// sol1(1);
        pick(N, Data,  M);
	}
	else if (M == 2) {
		sol2(1, 1);
	}
	else if (M == 3) {
		sol3(1);
	}

	return 0;
}