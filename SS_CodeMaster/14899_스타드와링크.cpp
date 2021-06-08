#include <iostream>
#include <iomanip>

using namespace std;
const int max_num = 20 + 1;

#define MIN(a,b) (a > b ? b : a)

int map[max_num][max_num];
int visitied[max_num];
int N, ans = 0xfffe;

void input()
{
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			map[i][j] = 0;
		}
	}
	ans = 0xfffe;

	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> map[i][j];
		}
	}
}

int diffPower()
{
	int starTeamSum = 0, linkTeamSum = 0;

	for (int i = 1; i <= N; i++) {
		if (visitied[i] == 1) {
			for (int j = 1; j <= N; j++) {
				if (visitied[j] == 1) {
					if (i == j)	continue;
					starTeamSum += map[i][j];
				}
			}
		}
		else {
			for (int j = 1; j <= N; j++) {
				if (visitied[j] == 0) {
					if (i == j)	continue;
					linkTeamSum += map[i][j];
				}
			}
		}
		
	}
	if (starTeamSum >= linkTeamSum) return starTeamSum - linkTeamSum;
	else return linkTeamSum - starTeamSum;
}

void combi(int idx, int cnt)
{
	if (cnt > N/2) {
		ans = MIN(ans, diffPower());
		return;
	}

	for (int i = idx; i <= N; i++) {
		if (visitied[i] == 1)	continue;
		visitied[i] = 1;
		combi(i + 1, cnt + 1);
		visitied[i] = 0;
	}
}

int main()
{
	std::cout.tie(0); std::cin.tie(0);
	int test_case = 1;
	/*freopen("14899_input.txt", "r", stdin);
	cin >> test_case;*/
	for (int i = 1; i <= test_case; i++) {
		input();
		combi(1, 1);
		cout << ans << endl;
		//cout <<"#" << i << " " << ans << endl;
	}
	
	return 0;
}