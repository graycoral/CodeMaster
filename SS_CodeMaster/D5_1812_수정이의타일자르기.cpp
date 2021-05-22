#include<iostream>
#define SWAP(a,b) {int t; t =a; a=b; b= t;}
using namespace std;

typedef struct Tile {
	int vertical;
	int column;
	bool alive;
} Tile;

const int maxN = 800 + 10;

Tile tile[maxN];
int sqAliv[maxN];
int tileIdx = 0;
int N, M;
int sq[maxN];
int makeTileCnt = 0;

void input()
{
	for (int i = 0; i < maxN; i++) {
		tile[i].vertical = tile[i].column = 0;
		tile[i].alive = false;
		sqAliv[i] = 0;
	}
	tileIdx = 0;
	makeTileCnt = 1;
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		cin >> sq[i];
	}
}

void Qsort(int* arr, int start, int end)
{
	if (start >= end)	return;
	int pivot = start;
	int i = start + 1;
	int j = end;

	while (i <= j) {
		while (i <= end && arr[i] >= arr[pivot]) {
			++i;
		}
		while (j > start&& arr[j] <= arr[pivot]) {
			--j;
		}
		if (i >= j)	break;
		SWAP(arr[i], arr[j]);
	}
	SWAP(arr[j], arr[pivot]);

	Qsort(arr, start, j - 1);
	Qsort(arr, j + 1, end);
}

int getLen(int m)
{
	if (m == 0)	return 1;
	else return 2 * getLen(m - 1);
}

void cutTile(int idx, int len)
{
	if (tile[idx].vertical > len) {
		tile[tileIdx].column = tile[idx].column;
		tile[tileIdx].vertical = tile[idx].vertical - len;
		tile[tileIdx++].alive = true;
	}

	if (tile[idx].column > len) {
		tile[tileIdx].vertical = len;
		tile[tileIdx].column = tile[idx].column - len;
		tile[tileIdx++].alive = true;
	}
	tile[idx].vertical = tile[idx].column = len;
	tile[idx].alive = false;
}

void sol()
{
	Qsort(sq, 0, N - 1);

	//int len = getLen(M);
	int len = M;

	tile[tileIdx].column = tile[tileIdx].vertical = len;
	tile[tileIdx++].alive = true;

	for (int i = 0; i < N; i++) {
		if (sqAliv[i] == 1)	continue;
		bool newTile = true;
		int sqLen = getLen(sq[i]);
		for (int t = 0; t < tileIdx; t++) {
			if (tile[t].alive == true && \
				tile[t].vertical >= sqLen && \
				tile[t].column >= sqLen) {
				//cut tile add tile
				cutTile(t, sqLen);
				sqAliv[i] = 1;
				newTile = false;
				break;
			}
		}
		if (newTile) {
			tile[tileIdx].column = tile[tileIdx].vertical = len;
			tile[tileIdx++].alive = true;
			//cut tile add tile
			cutTile(tileIdx - 1, sqLen);
			sqAliv[i] = 1;
			makeTileCnt++;
		}
	}
}

int main()
{
	int test_case;

	//freopen("1812_input.txt", "r", stdin);
	cin >> test_case;

	for (int i = 1; i <= test_case; i++) {
		input();
		sol();
		cout << "#" << i << " " << makeTileCnt << endl;
	}
	return 0;
}