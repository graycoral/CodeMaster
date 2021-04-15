#include <iostream>
#include <cstring>
/*
#4 10
#5 7 //
#6 1111
#1 8 //
#2 17 //
#7 24 //
#8 0 //
#3 16 //
*/

using namespace std;

const int maxn = 1000 + 1;

enum DIR {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

typedef struct pos {
	int r, c;
	int dir;
	int e;
} pos;

typedef struct Result {
	int preIdx;
	double sec;
}Result;

pos map[maxn];
Result visitied[maxn];
int N;

void input()
{
	memset(&map, 0, sizeof(struct pos)* maxn);
	memset(&visitied, 0, sizeof(struct Result)*maxn);
	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> map[i].c;
		cin >> map[i].r;		
		cin >> map[i].dir;
		cin >> map[i].e;

		map[i].c += 1000;
		map[i].r += 1000;

		visitied[i].preIdx = 0xfffe;
		visitied[i].sec = 0xfffe;
	}
}

void calBombSec(int idx)
{
	if (idx == -1)	return;

	Result minSec{ 0xfffe, 0xfffe };

	for (int i = 0; i < N; i++) {
		double sec = 0xfffe;
		if (idx == i)	continue;
#if 0
		if ((map[idx].dir == UP && map[i].dir == DOWN && map[idx].r < map[i].r) || \
			(map[idx].dir == DOWN && map[i].dir == UP && map[idx].r > map[i].r) || \
			(map[idx].dir == LEFT && map[i].dir == RIGHT && map[idx].c > map[i].c) || \
			(map[idx].dir == RIGHT && map[i].dir == LEFT && map[idx].c < map[i].c)) {
			if (map[idx].r == map[i].r)			sec = (map[idx].c - map[i].c) / 2;
			else if (map[idx].c == map[i].c)	sec = (map[idx].r - map[i].r) / 2;
		}
		else {
			// idx : R , i : U
			if ((map[idx].r > map[i].r&& map[idx].c < map[i].c && (map[idx].dir == RIGHT && map[i].dir == UP) ||
				(map[idx].r < map[i].r && map[idx].c > map[i].c && map[idx].dir == UP && map[i].dir == RIGHT)))
			{
				sec = map[idx].c - map[i].c;
			}
			// idx : R , i : D
			else if ((map[idx].r > map[i].r&& map[idx].c < map[i].c && map[idx].dir == RIGHT && map[i].dir == DOWN) \
				|| (map[idx].r < map[i].r && map[idx].c > map[i].c && map[idx].dir == DOWN && map[i].dir == RIGHT))
			{
				sec = map[idx].c - map[i].c;
			}
			// UP & LEFT
			else if ((map[idx].r < map[i].r && map[idx].c < map[i].c && (map[idx].dir == UP && map[i].dir == LEFT)) || \
				((map[idx].r > map[i].r&& map[idx].c > map[i].c&& map[idx].dir == LEFT && map[i].dir == UP)))
			{
				sec = map[idx].c - map[i].c;
			}
			// DOWN & LEFT
			else if (((map[idx].r > map[i].r&& map[idx].c < map[i].c && map[idx].dir == DOWN && map[i].dir == LEFT)) || \
				(map[idx].r < map[i].r && map[idx].c > map[i].c && map[idx].dir == LEFT && map[i].dir == DOWN))
			{
				sec = map[idx].c - map[i].c;
			}
		}
#endif


		if (sec < 0) sec *= -1;

		if (sec > visitied[idx].sec || (sec == 0xfffe) || sec > visitied[i].sec)	continue;
		if (minSec.sec < sec)	continue;
		/*
		Result& preSec = visitied[i];
		if (preSec.preIdx == 0xfffe) {
			if (visitied[idx].preIdx != 0xfffe && (visitied[visitied[idx].preIdx].preIdx != 0xfffe) \
				&& visitied[visitied[idx].preIdx].sec > sec) {
				visitied[visitied[idx].preIdx].preIdx = 0xfffe;
				visitied[visitied[idx].preIdx].sec = 0xfffe;				
			}
			int preIdx = visitied[idx].preIdx;
			visitied[idx].preIdx = i;
			visitied[idx].sec = sec;

			preSec.preIdx = idx;
			preSec.sec = sec;

			minSec.sec = sec;
			minSec.preIdx = i;
			calBombSec(preIdx);
		}
		else {
			int preIdx = visitied[idx].preIdx;
			visitied[preIdx].preIdx = 0xfffe;
			visitied[preIdx].sec = 0xfffe;


			if (preSec.sec > sec) {
				visitied[preSec.preIdx].preIdx = 0xfffe;
				visitied[preSec.preIdx].sec = 0xfffe;

				preSec.preIdx = idx;
				preSec.sec = sec;
				visitied[idx].preIdx = i;
				visitied[idx].sec = sec;

				minSec.sec = sec;
				minSec.preIdx = i;
			}
			else if (preSec.sec == sec) {
				preSec.preIdx = idx;
				preSec.sec = sec;
				visitied[idx].preIdx = i;
				visitied[idx].sec = sec;

				minSec.sec = sec;
				minSec.preIdx = i;
			}
		}
		*/
		

		int idxPreidx = visitied[idx].preIdx;
		int iPreidx = visitied[i].preIdx;
		
		visitied[i].preIdx = idx;
		visitied[idx].preIdx = i;

		visitied[i].sec = sec;
		visitied[idx].sec = sec;

		if (idxPreidx != 0xfffe) {
			visitied[idxPreidx].preIdx = 0xfffe;
			visitied[idxPreidx].sec = 0xfffe;
			calBombSec(idxPreidx);
		}
		if (iPreidx != 0xfffe) {
			visitied[iPreidx].preIdx = 0xfffe;
			visitied[iPreidx].sec = 0xfffe;
			calBombSec(iPreidx);
		}
		
	}

	if (minSec.sec == 0xfffe) {
		visitied[idx].preIdx = 0xfffe;
		visitied[idx].sec = 0xfffe;
	}
}

int bomb()
{	
	int sum = 0;
	for (int i = 0; i < N; i++) {
		calBombSec(i);
	}

	for (int i = 0; i < N; i++) {
		if (visitied[i].preIdx != 0xfffe) {
			sum += map[i].e;
		}
	}

	return sum;
}




int sol()
{
	for (int i = 0; i < 4000; i++) {
		for (int j = 0; j < N; j++) {
			int& x = map[j].c;
			int& y = map[j].r;

		}
	}

	return 0;
}




int main()
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	//freopen("모의고사_5648_원자소멸.txt", "r", stdin);
	
	int T;
	cin >> T;

	for (int i = 0; i < T; i++) {
		input();
		cout << "#" << i+1 << " "<< bomb() << endl;
	}


	return 0;
}