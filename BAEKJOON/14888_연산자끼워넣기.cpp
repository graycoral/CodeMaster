#include <iostream>

using namespace std;
const int maxn = 101;

int N;
int num[maxn];
int cal[4];
int total_cnt;
int maxSum;
int minSum = 0xfffe;


int calSum(int sum, int nextIdx)
{
    if(nextIdx >= N) return sum;

    for(int i=0; i<4; i++) {
        if(cal[i] == 0) continue;
        cal[i]--;
        if(i == 0) {
            sum += num[nextIdx];
            sum = calSum(sum, nextIdx +1);
        }
        else if(i == 1) {
            sum -= num[nextIdx];
            sum = calSum(sum, nextIdx +1);
        }
        else if(i == 2) {
            sum *= num[nextIdx];
            sum = calSum(sum, nextIdx +1);
        }
        else if(i == 3) {
            sum /= num[nextIdx];
            sum = calSum(sum, nextIdx +1);
        }
        cal[i]++;
    }
    maxSum = maxSum < sum ? sum : maxSum;
    minSum = minSum > sum ? sum : minSum;

    return sum;
}

int main()
{
    //freopen("../input/14888_연산자끼워넣기.txt", "r", stdin);
    int T = 1;
    //cin >> T;

    for(int i=0; i<T; i++) {
        int tmp;
		minSum = 0xfffe;
		maxSum = 0;
        cin >> N;
        for(int j = 0; j < N; j++) {
            cin >> tmp;
            num[j] = tmp;
        }

        for(int calIdx=0; calIdx<4; calIdx++){
            int tmpcal;
            cin >> tmpcal;
            cal[calIdx] = tmpcal;
        }
		
		calSum(num[0], 1);

        cout << maxSum << endl;
        cout << minSum << endl;
    }
    return 0;
}