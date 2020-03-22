#include <iostream>
#include <vector>
#include <string>

using namespace std;

class BaseMenu
{
    string title;
public:
    BaseMenu(string s) : title(s) {}
    string getTile() const { return title;}
    // !! 제공할 것이 없더라도 모든 메뉴의 공통 부분이라면 순수가상함수로 제공 해야함
    virtual void command() = 0;
    virtual BaseMenu* getSubMenu(int idx) 
    { 
        // throw "unsupport fuction"     
        return 0;
    }
    virtual void addMenu(BaseMenu* p) 
    {
        throw "unsupport fuction";
    }
};

// 핵심
class PopupMenu : public BaseMenu
{
    vector<BaseMenu*> v;
public:
    PopupMenu(string s):BaseMenu(s) {}
    void addMenu(BaseMenu* p) {v.push_back(p);}
    virtual void command()
    {        
       while(1)
       {
           system("cls");
            int sz = v.size();
            for(int i=0; i < sz; i++){
                cout << i+1 << "." << v[i]->getTile() << endl;           
            }
            //----------------------
            int cmd;
            cout << "select munu";
            cin>> cmd;

            if(cmd < 1 || cmd > sz+1)   continue;
            if(cmd == sz +1)    break;

            // 선택 된 메뉴 실행
            v[cmd-1]->command(); // 핵심!!
       }       
    }
    BaseMenu* getSubMenu(int idx)
    {
        return v[idx];
    }
};