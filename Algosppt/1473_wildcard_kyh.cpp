#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <string.h>

using namespace std;

int N;
int cache[101][101];
vector<string> anw;
string W, S;

bool CheckMatchedMemoi(int w, int s)
{
    int& ret = cache[w][s];
    if (ret != -1)   return ret;
    while (w < W.size() && s < S.size() && (W[w] == '?' || W[w] == S[s])) {
        ++w; ++s;
    }
    if (w == W.size() && s == S.size()) return ret = true;

    if (W[w] == '*')
    {
        for (int skip = 0; skip + s <= S.size(); skip++)
        {
            if (CheckMatchedMemoi(w + 1, s + skip))
                return ret = true;
        }
    }

    return ret = false;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> W;
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> S;
        memset(cache, -1, sizeof(cache));
        if (CheckMatchedMemoi(0, 0)) {
            anw.push_back(S);
        }
        S.clear();
    }

    sort(anw.begin(), anw.end());

    for (auto iter : anw) {
        cout << iter << endl;
    }

    return 0;
}