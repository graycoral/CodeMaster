#include <iostream>
#include <iomanip>
using namespace std;

int visited[1000];
int saved[1000];
int N = 5;

void powerset(int start, int cnt)
{
	if (start > cnt) {
		for (int i = 1; i <= N; i++) {
			if (saved[i] == 0) continue;
			cout << setw(2) << saved[i];
		}
		cout << endl;
		return;
	}

	for (int i = start; i <= N; i++) {
		if (visited[i] == 1)	continue;
		visited[i] = 1;
		saved[start] = i;
		powerset(i + 1, cnt);
		visited[i] = 0;
		saved[start] = 0;
	}
}

int per[10000];

void permutation(int start, int cnt)
{
	if (start > cnt) {
		for (int i = 1; i <= cnt; i++) {
			cout << setw(2) << per[i];
		}
		cout << endl;
		return;
	}
	for (int i = 1; i <= N; i++) {
		per[start] = i;
		permutation(start + 1, cnt);
	}
}

int per1[10000];
int vper1[10000];
void combi(int start, int cnt)
{
	if (start > cnt) {
		for (int i = 1; i <= cnt; i++) {
			cout << setw(2) << per1[i];
		}
		cout << endl;
		return;
	}
	for (int i = 1; i <= N; i++) {
		if (vper1[i] == 1)	continue;
		vper1[i] = 1;
		per1[start] = i;
		combi(start + 1, cnt);
		vper1[i] = 0;
	}
}


int main()
{
	for (int i = 0; i < (1 << N); i++) {
		for (int j = 0; j < N; j++) {
			if (i & (j << N)) {
				cout << j << " ";
			}
			
		}
		cout << endl;
	}
	cout << endl << endl;
	
	/*permutation(1, 3);
	cout << endl << endl;*/
	/*combi(1, 3);
	cout << endl << endl;*/
	//powerset(1, 5);
	

}