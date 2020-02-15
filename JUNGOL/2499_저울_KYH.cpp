#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
int N;
vector<int> Input;
void input()
{
    cin >> N;
    for(int i=0; i<N; i++){
        int tmp;
        cin >> tmp;
        Input.push_back(tmp);
    }
}

void sol()
{
    sort(Input.begin(), Input.end());
    int sum = 1;
    for(int i=0; i<N && sum >= Input[i]; i++){
        sum += Input[i];
    }
    cout << sum << endl;
}

int main()
{
    input();
    sol();
    return 0;
}