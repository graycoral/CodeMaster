#include <iostream>
#include <algorithm>

using namespace std;
string reverser(string::iterator& it)
{
    char head = *it;
    ++it;
    if(head == 'b' || head == 'w')  return string(1, head);

    string upperLeft  = reverser(it);
    string upperRight = reverser(it);
    string lowerLeft = reverser(it);
    string lowerRight = reverser(it);

    return string("x") + lowerLeft + lowerRight + upperLeft + upperRight;
}


int main()
{
    int tc;
    cin >> tc;
    while(tc--)
    {
        string quadTree;
        cin >> quadTree;
        string::iterator it = quadTree.begin();
        cout << reverser(it) << endl;
    }
}
