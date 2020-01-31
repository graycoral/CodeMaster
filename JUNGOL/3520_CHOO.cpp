// http://www.jungol.co.kr/bbs/board.php?bo_table=pbank&wr_id=2860&sca=30
// 3520 : Tutorial : stl-sort
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

typedef struct{
    char Name[10];
    int Pi;
    int ID;
}Data;

struct Comparator{
    bool operator()(const Data&a, const Data&b){
        
        // 선호 숫자의 내림차순을 1순위로
        if(a.Pi != b.Pi) return a.Pi > b.Pi;
        
        // 이름의 오름차순을 2순위로
        int ret = strcmp(a.Name, b.Name);
        if(ret != 0) return ret < 0;

        // ID의 오름차순을 3순위로 정렬
        return a.ID < b.ID; 
    }
}compObject;

int N;
int Q;

vector<Data> arr;

int main(void){
    scanf("%d %d", &N, &Q);

    for(int i=1; i<=N; i++){
        Data temp_d;
        scanf("%s %d",temp_d.Name, &temp_d.Pi);
        temp_d.ID = i;
        arr.push_back(temp_d);
    }

    sort(arr.begin(), arr.end(), Comparator());

    for(auto d : arr)
        printf("%d ", d.ID);

    return 0;
}
