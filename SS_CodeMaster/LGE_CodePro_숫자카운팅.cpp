#include <iostream>
#include <stdio.h>
using namespace std;

#define MAX ((int)2e5) 

int N;
long long int A[MAX + 10];
int M;

void Sol() {
	cin >> N; 
	for (int i = 0; i < N; i++) {
		long long int tmp;
		cin >> tmp;
		A[tmp]++;
	}
	cin >> M;
	for (int i = 0; i < M; i++) {
		long long int tmp;
		cin >> tmp;
		cout << A[tmp] << " ";
	}
}

int main(void) {
	Sol();
	return 0;
}