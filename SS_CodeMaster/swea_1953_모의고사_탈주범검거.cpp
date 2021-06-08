#include <iostream>

using namespace std;

const int max_num = 51;
const int dr[] = {-1, 1, 0, 0};
const int dc[] = {0, 0, -1, 1};
int map[max_num][max_num];
int visted[max_num][max_num];
int N, M;
int startR , startC, L;
int ans =0;

typedef struct Pos {
    int r,c;
} Pos;

Pos q[max_num * max_num];
int front, last;

int direction[8][4] = {
    {1, 1, 1, 1},
    {1, 1, -1, -1},
    {-1, -1, 1, 1},
    {-1, 1, 1, -1},
    {1, -1, 1, -1},
    {1, -1, -1, 1},
    {-1, 1, -1, 1}
};

void input()
{
    for(int i = 0; i <= N ;i++) {
        for(int j = 0; j<= N; j++) {
            map[i][j] = visted[i][j] = 0;
        }
    }

    front = last = 0;
    cin >> N >> M >> startR >> startC >> L;

    for(int r = 0 ; r < N; r++) {
        for(int c= 0; c <M; c++) {
            cin >> map[r][c];
        }
    }
}

void push(int r, int c, int t)
{
    if(r >= N || c >= M || r <0 || c< 0)    return;
    if(visted[r][c])    return;
    if(map[r][c] == 0)  return;

    q[front].r = r;
    q[front++].c= c;
    visted[r][c] = t;
}

Pos pop()
{
    return q[last++];
}

int empty()
{
    return front == last ? 1 : 0;
}

void sol()
{
    int t = 1;
    push(startR, startC, t++);
    while(!empty()) {
        int timlFlag = 0;
        Pos cur = pop();

        if(map[cur.r][cur.c] == 1) {
            for(int i = 0; i < 4; i++) {
                int nr = cur.r+dr[i];
                int nc = cur.c+dc[i];
				if (nr >= N || nc >= M || nr < 0 || nc < 0)    continue;
                if(direction[map[nr][nc]][i] == -1)   continue;
                push(nr, nc, t);
                timlFlag =1;
            }
            if(timlFlag) t++;
        }
        else if(map[cur.r][cur.c] == 2) {
           for(int i = 0; i < 2; i++) {
                int nr = cur.r+dr[i];
                int nc = cur.c+dc[i];
				if (nr >= N || nc >= M || nr < 0 || nc < 0)    continue;
                if(direction[map[nr][nc]][i] == -1)   continue;
                push(nr, nc, t);
				timlFlag = 1;
            }
            if(timlFlag) t++;
        }
        else if(map[cur.r][cur.c] == 3) {
            for(int i = 2; i < 4; i++) {
                int nr = cur.r+dr[i];
                int nc = cur.c+dc[i];
				if (nr >= N || nc >= M || nr < 0 || nc < 0)    continue;
                if(direction[map[nr][nc]][i] == -1)   continue;
                push(nr, nc, t);
				timlFlag = 1;
            }
            if(timlFlag) t++;
        }
        else if(map[cur.r][cur.c] == 4) {
			int nr = cur.r + dr[0];
			int nc = cur.c + dc[0];
			if (nr >= N || nc >= M || nr < 0 || nc < 0)    continue;
            if(direction[map[nr][nc]][1]) {
                push(nr, nc, t);
                timlFlag =1;
            }

			nr = cur.r + dr[3];
			nc = cur.c + dc[3];
			if (nr >= N || nc >= M || nr < 0 || nc < 0)    continue;
            if(direction[map[nr][nc]][2]){
                push(nr, nc, t);
                timlFlag =1;
            }
            if(timlFlag) t++;
        }
        else if(map[cur.r][cur.c] == 5) {
			int nr = cur.r + dr[1];
			int nc = cur.c + dc[1];
			if (nr >= N || nc >= M || nr < 0 || nc < 0)    continue;
            if(direction[map[nr][nc]][0]) {
                push(nr, nc, t);
                timlFlag =1;
            }

			nr = cur.r + dr[3];
			nc = cur.c + dc[3];
			if (nr >= N || nc >= M || nr < 0 || nc < 0)    continue;
			if (direction[map[nr][nc]][2]) {
				push(nr, nc, t);
				timlFlag = 1;
			}
            if(timlFlag) t++;
        }
        else if(map[cur.r][cur.c] == 6) {
			int nr = cur.r + dr[1];
			int nc = cur.c + dc[1];
			if (nr >= N || nc >= M || nr < 0 || nc < 0)    continue;
			if (direction[map[nr][nc]][0]) {
				push(nr, nc, t);
				timlFlag = 1;
			}

			nr = cur.r + dr[2];
			nc = cur.c + dc[2];
			if (nr >= N || nc >= M || nr < 0 || nc < 0)    continue;
			if (direction[map[nr][nc]][3]) {
				push(nr, nc, t);
				timlFlag = 1;
			}
			if (timlFlag) t++;
       }
        else if(map[cur.r][cur.c] == 7) {
			int nr = cur.r + dr[0];
			int nc = cur.c + dc[0];
			if (nr >= N || nc >= M || nr < 0 || nc < 0)    continue;
			if (direction[map[nr][nc]][1]) {
				push(nr, nc, t);
				timlFlag = 1;
			}

			nr = cur.r + dr[2];
			nc = cur.c + dc[2];
			if (nr >= N || nc >= M || nr < 0 || nc < 0)    continue;
			if (direction[map[nr][nc]][3]) {
				push(nr, nc, t);
				timlFlag = 1;
			}
			if (timlFlag) t++;
        }
    }

	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++) {
			if (visted[r][c] <= L && visted[r][c] > 0) ans++;
		}
	}
}

int main()
{
    int test_case = 1;

    freopen("swea_모의고사_탈주범검거.txt", "r", stdin);
    cin >> test_case;
    for(int i = 1; i<=test_case; i++) {
        input();
        sol();
        cout << "#" << i << " " << ans <<endl;
    }
    return 0;
}