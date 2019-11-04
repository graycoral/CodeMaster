#include <iostream>
#include <map>
#include <utility>
#include <algorithm>
using namespace std;

map <int,int>candidates;
int ans;

bool is_dominated(int paper, int interview)
{
    map <int,int>::iterator it = candidates.lower_bound(paper);
    
    if(it == candidates.begin()) return false;
    else{
        --it;
        return it->second < interview;
    }
}

void remove_candidate(int paper, int interview)
{
    map <int,int>::iterator it = candidates.lower_bound(paper);

    while(it != candidates.end())
    {
        if(it->second < interview)
            break;

        if(it->second > interview)
        {
            map <int,int>::iterator jt = it;
            jt++;
            candidates.erase(it);
            ans--; 
            it = jt;
            // it++;
            // 
            // candidates.erase(jt);
        }
    }
}

void enroll_candidate(int paper, int interview)
{   
    if(is_dominated(paper, interview))
    {
        return;
    } 
    
    remove_candidate(paper, interview);

    candidates[paper] = interview;
    ans++;    
}

int main(void){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T, N;
    int paper, interview;
    cin >> T;

    while(T--){
        cin >> N;
        ans = 0;
        for(int i=0; i<N; i++){
            cin >> paper >> interview;
            enroll_candidate(paper, interview);
        }
        candidates.clear();
        cout << ans << endl;
    }

    return 0;
}




