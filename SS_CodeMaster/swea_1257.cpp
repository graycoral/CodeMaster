#include <iostream>
#include <cstring>
using namespace std;

char arr[400 + 1];
int k;

typedef struct Node {
	bool check;
	struct Node* next[27];
}Node;

void counting_sort(int size)
{
	int sorted_input[26];

	for (int i = 0; i < 26; i++) {
		sorted_input[i] = 0;
	}

	for (int i = 0; i < size; i++) {
		sorted_input[arr[i] -'a']++;
	}

	int idx = 0;
	
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < sorted_input[i]; j++) {
			arr[idx++] = i + 'a';
		}
	}
}

void sol(int test_case, int size)
{
	int idx = k;
	int word_len = 1;
	int word_idx = size;

	while (idx >= 0 && word_len <= size) {
		idx -= word_idx;
		word_idx = size - word_len++;
	}

	if (idx > 0) {
		cout << "#" << test_case << " "<< "none" << endl;
	}
	else {
		cout << "#" << test_case << " ";
		word_len--;
		idx += (size - word_len);
		
		for (int i = 0; i < word_len; i++) {
			cout << arr[idx -1 + i];
		}
		cout << endl;
	}
}

int T, K, cnt, flag;

char q[401 * 10];
int front, last;

void push(char d)
{
	q[front++] = d;
}

char pop()
{
	return q[last++];
}

Node* makeNode()
{
	Node* tmp = new(Node);
	for (int i= 0; i < 27; i++) {
		tmp->next[i] = 0;
	}
	tmp->check = false;

	return tmp;
}

void insert(Node* root, char* buff, int st, int ed)
{
	Node* tmpRoot = root;
	if (st == ed)	return;
	if (!tmpRoot->next[buff[st] - 'a']) {
		tmpRoot->next[buff[st] - 'a'] = makeNode();
	}
	insert(tmpRoot->next[buff[st] - 'a'], buff, st + 1, ed);
}

void find(Node* root)
{
	Node* tmpRoot = root;
	if (cnt == k) {
		flag = 1;
		return;
	}

	for (int i = 0; i < 27; i++) {
		if (tmpRoot->next[i]) {
			push(i + 'a');
			if (!tmpRoot->next[i]->check)	cnt++;
			find(tmpRoot->next[i]);
			if (flag)	return;
			pop();
		}
	}
}

void delNode(Node* root)
{
	Node* tmp = root;
	for (int i = 0; i < 27; i++) {
		if (tmp->next[i]) delNode(tmp->next[i]);
	}
	free(tmp);
}


int main()
{
	int test_case = 1;

	freopen("swea_1257_input.txt", "r", stdin);
	cin >> test_case;
	for (int i = 1; i <= test_case; i++) {
		cin >> k >> arr;
		counting_sort(strlen(arr));
		sol(i, strlen(arr));
		
	}
	return 0;
}