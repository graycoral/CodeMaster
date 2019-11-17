#include <iostream>
#include <list>
#include <iterator>

using namespace std;

list <int> l;

int N;//직원 수
int S;//시작 직원 번호
int M;

void InputData(){
	cin >> N >> S >> M;
}
int main(){

	InputData();//	입력 함수

	//	코드를 작성하세요
	for(int i=1; i<=N; i++) l.push_back(i);
	
	list <int>::iterator it = l.begin();
	advance(it, S-1);
	
	while(!l.empty()){
		int dist = distance(l.begin(), it);
		//cout << dist << " ";
		if((dist + M-1) >= N){
			it = l.begin();
			int step = (dist+M-1)%(N);
			//cout << step << endl;
			advance(it, step);
			N--;
		}
		else{
			advance(it, M-1);
			//cout << M-1 << endl;
			N--;
		}
		cout << *it << " ";
		list <int>::iterator temp = it;
		it++;
		l.erase(temp);
	}
	
	return 0;
}