#include <iostream>
#include <vector>
#include <string>

using namespace std;

class BaseMenu
{
    string title_;
public:
    BaseMenu(string s) : title_(s) {}

    string getTitle()   { return title_; }
    virtual void commmand() = 0;
};

class MenuItem : public BaseMenu
{
    int id;
public:
    MenuItem(string s, int n) : BaseMenu(s), id(n) {}
    virtual void commmand()
    {
        cout << getTitle() << "메뉴 선택 됨" << endl;
        getchar();
    }
};

class PopupMenu : public BaseMenu
{
    vector<BaseMenu*> v;
public:
    PopupMenu(string s) : BaseMenu(s) {}

    void addMenu(BaseMenu* p)   { v.push_back(p); }

    virtual void command()
    {
        system("cls");
        int sz = v.size();
        for(int i=0; i<sz; i++) {
            cout << i +1  << "." << v[i]->getTitle() << endl;
        }
        cout << sz +1 << ". 상위 매뉴로"<< endl;
    }
};