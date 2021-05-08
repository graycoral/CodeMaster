#include <iostream>
#include <iomanip>

using namespace std;

const int maxN = 25+1;
const int maxM = 100+1;

int map[maxN][maxN];
int visited[maxN][maxN];
int N, M;
int centerPosR;
int centerPosC;
int ans;

int dr[] = {0, 1, 0, -1};
int dc[] = {1,0, -1, 0};

typedef struct Round {
    int d, c;
} Round;

Round round[maxM];

void input()
{
    ans = 0;
    centerPosR = centerPosC = 0;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            map[i][j] = visited[i][j] = 0;
        }
    }

    for(int i=0; i<M; i++) {
        round[i].d = round[i].c = 0;
    }
    cin >> N >> M;
    centerPosC = centerPosR = N/2;

    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> map[i][j];
        }
    }
    for(int i=0; i<M; i++) {
        cin >> round[i].d >> round[i].c;
    }
}

#define DEBUG (1)
void show(int m)
{
#if DEBUG
    cout << "=====================" << m << "=====================" <<endl;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cout << setw(3) << map[i][j];
        }
        cout << endl;
    }
    cout << "==========================================" <<endl;
#endif
}

bool invalidRange(int r, int c)
{
    return (r < 0 || c < 0 || r >= N || c >= N) ? 1 : 0 ;
}

void remove(int idx)
{
    Round rm = round[idx];

    int nr= centerPosR; int nc = centerPosC;
    for(int i = 0; i< rm.c; i++) {
        nr += dr[rm.c]; nc += dc[rm.c];
        if(invalidRange(nr, nc)) continue;
        map[nr][nc] = 0;
    }
}

void reorder()
{
    int oriArr[maxN * maxN + 1] = {0};
    int oriIdx = 0; int reIdx = 0;
    int moveCnt = 0;
    int dic[4] = {2,1,0,3};
    int nr = centerPosR; int nc = centerPosC;
    int idx = 1;

    while(!invalidRange(nr, nc)) {
        int cnt = idx * 2;
        while(cnt--) {
            nr += dr[dic[moveCnt%4]];
            nc += dr[dic[moveCnt%4]];
            if(map[nr][nc] == 0)    continue;
            oriArr[oriIdx++] = map[nr][nc];
        }
        moveCnt++;
        idx++;
    }

    int newidx= 0;
    nr = centerPosR; nc = centerPosC;
    idx = 1;
    while(!invalidRange(nr, nc)) {
        int cnt = idx * 2;
        while(cnt--) {
            nr += dr[dic[moveCnt%4]];
            nc += dr[dic[moveCnt%4]];
            map[nr][nc] = oriArr[newidx++];
        }
        moveCnt++;
        idx++;
    }
}

int move(int r, int c, int value)
{
    int retValue = 0;
    if(map[r][c] != value)  return retValue;

    visited[r][c] = 1;
    retValue = 1;
    map[r][c] = 0;

    for(int i= 0; i < 4; i++) {
        if(!invalidRange(r + dr[i], c + dc[i])) {
            retValue += move(r + dr[i], c + dc[i], value);
        }
    }

    return retValue;
}

void checkPatter()
{
    int retCnt = 0;
    for(int r = 0; r<N; r++) {
        for(int c =0 ;c <N; c++){
            int retCnt = 0;
            if(visited[r][c] == 1)    continue;
            if(!invalidRange(r,c)) {
                int mapValue = map[r][c];
                retCnt = move(r, c, mapValue);
                ans += (retCnt * mapValue);
            }
        }
    }
}

void reArrange()
{
    int oriArr[maxN * maxN + 1] = {0};
    int reArr[maxN * maxN + 1] = {0};
    int oriIdx = 0; int reIdx = 0;
    int moveCnt = 0;
    int dic[4] = {2,1,0,3};
    int nr = centerPosR; int nc = centerPosC;
    int idx = 1;

    while(!invalidRange(nr, nc)) {
        int cnt = idx * 2;
        while(cnt--) {
            nr += dr[dic[moveCnt%4]];
            nc += dr[dic[moveCnt%4]];
            oriArr[oriIdx++] = map[nr][nc];
        }
        moveCnt++;
        idx++;
    }

    for(int i= 0; i< oriIdx ; i++) {
        int val = oriArr[i];
        int checkIdx = i;
        int cnt = 0;

        while(val == oriArr[checkIdx]) {
            cnt++; checkIdx++;
        }
        reArr[reIdx++] = oriArr[i];
        reArr[reIdx++] = cnt;
        i = checkIdx;
    }

    int newidx= 0;
    nr = centerPosR; nc = centerPosC;
    idx = 1;
    while(!invalidRange(nr, nc)) {
        int cnt = idx * 2;
        while(cnt--) {
            nr += dr[dic[moveCnt%4]];
            nc += dr[dic[moveCnt%4]];
            map[nr][nc] = reArr[newidx++];
        }
        moveCnt++;
        idx++;
    }
}

void sol()
{
    int idx = M;
    while(idx--) {
        show(M-idx);
        remove(M-idx);
        reorder();
        checkPatter();

        for(int r= 0; r<N; r++) {
            for(int c=0; c<N; c++) {
                visited[r][c] = 0;
            }
        }
    }
}

int main()
{
    int test_case = 1;
    freopen("미로타워티펜스.txt", "r", stdin);

    cin >> test_case;

    for(int i =1; i <= test_case; i++) {
        input();
        sol();
        cout << "#" << i << " " << ans << endl;
    }

    return 0;
}