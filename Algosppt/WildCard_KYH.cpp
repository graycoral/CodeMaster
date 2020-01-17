#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

int N;
int cache[101][101];
vector<string> anw;
string W, S;
int cnt = 0;

bool CheckMatchedMemoi(int w, int s)
{
	int& ret = cache[w][s];
	if (ret == -1)   return ret;
	while (w < W.size() && s < S.size() && (W[w] == '?' || W[w] == S[s])) {
		++w; ++s;
	}
	if (w == W.size()) return s == S.size();

	if (W[w] == '*') {
		for (int skip = 0; skip + s <= S.size(); ++skip) {
			if (CheckMatchedMemoi(w + 1, s + skip))  return true;
		}
	}

	return false;
}

void init()
{
	for (int i = 0; i < 101; i++) {
		for (int j = 0; j < 101; j++) {
			cache[i][j] = 0;
		}
	}
	W.clear();
	S.clear();
	anw.clear();
	cnt = 0;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int tc;
	cin >> tc;

	for (int i = 0; i < tc; i++) {
		init();
		cin >> W;
		cin >> N;
		for (int j = 0; j < N; j++) {
			S.clear();
			cin >> S;
			auto iter = find(anw.begin(), anw.end(), S);
			if (iter == anw.end()) {
				if (CheckMatchedMemoi(0, 0)) {
					anw.push_back(S);
					cnt++;
				}
			}
		}
		sort(anw.begin(), anw.end());
		for (int i = 0; i < cnt; i++) {
			cout << anw[i] << endl;
		}
		/*
		for (auto s : anw) {
			cout << s << endl;
		}
		*/
	}
	return 0;
}