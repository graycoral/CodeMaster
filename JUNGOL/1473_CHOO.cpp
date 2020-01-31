// http://www.jungol.co.kr/bbs/board.php?bo_table=pbank&wr_id=745&sca=99&sfl=wr_subject&stx=%EC%99%80%EC%9D%BC%EB%93%9C
// 1473 : 와일드카드
#include <iostream>
#include <string>
#include <vector>
#include <string.h>
#include <algorithm>

using namespace std;

#define MAX_N 50
#define MAX_STRING_LEN 100

int N;
string W, F;
vector<string> ans;
int cache[MAX_STRING_LEN][MAX_STRING_LEN];

int is_matched(int w, int f){
    int &ret = cache[w][f];
    if(ret != -1) return ret;

    while(w<W.size() && f<F.size() && (W[w]=='?' || W[w]==F[f]))
        w++, f++;
    
    if(w==W.size() && f==F.size()) return ret = true;

    if(W[w]=='*')
    {
        for(int skip = 0; f+skip<=F.size(); skip++)
        {
            if(is_matched(w+1,f+skip))
                return ret = true;
        }
    }
    return ret = false;
}

int main(void){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> W;
    cin >> N;
    for(int i=0; i<N; i++){
        cin >> F;
        memset(cache, -1, sizeof(cache));
        if(is_matched(0,0))
            ans.push_back(F);
        F.clear();
    }

    sort(ans.begin(), ans.end());

    for(auto s : ans)
        cout << s << endl;

    return 0;
}