#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define TEST (2)

#if TEST == 1
// Composite 패턴을 활용한 메뉴 만들기
/*
    @startuml
    title Composite Pattern
    class BaseMenu {
        string title;
        commmand() = 0
    }
    class MenuItem {

    }
    class PopupMenu {

    }
    BaseMenu <|-down- MenuItem
    BaseMenu <|-down- PopupMenu
    @enduml
    
*/

class BaseMenu
{
    string title;
public:
    BaseMenu(string s) : title(s) {}
    string getTile() const { return title;}
    // !! 제공할 것이 없더라도 모든 메뉴의 공통 부분이라면 순수가상함수로 제공 해야함
    virtual void command() = 0; 
};

class MenuItem : public BaseMenu
{
    int id;
public:
    // MenuItem(int n) : id(n) {} - c++ 기본 문법 참조 
    MenuItem(string s, int n) : BaseMenu(s), id(n) {}
    virtual void command()
    {
        cout << getTile() << endl;
        getchar();
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
        /*
            1. 해상도 설정
            2. 명암설정
            3. 상위 메뉴로 
        */
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
};

int main()
{
    PopupMenu pm("화면 설정");
}

#elif TEST ==2
// 사용

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

class MenuItem : public BaseMenu
{
    int id;
public:
    // MenuItem(int n) : id(n) {} - c++ 기본 문법 참조 
    MenuItem(string s, int n) : BaseMenu(s), id(n) {}
    virtual void command()
    {
        cout << getTile() << endl;
        getchar();
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

int main()
{
    PopupMenu* menubar = new PopupMenu("MenuBar");
    PopupMenu* pm1 = new PopupMenu("화면 설정");
    PopupMenu* pm2 = new PopupMenu("화면 설정");
    MenuItem* m1 = new MenuItem("화면 설정", 11);

    menubar->addMenu(pm1);
    menubar->addMenu(pm2);
    menubar->addMenu(m1);

    pm1->addMenu(new MenuItem("해상도변경", 21));
    pm1->addMenu(new MenuItem("명암변경", 22));

    pm1->addMenu(new MenuItem("음량변경", 31));   
    BaseMenu* p= menubar->getSubMenu(1)->getSubMenu(0);
    menubar->getSubMenu(1)->addMenu(new MenuItem("AA",100));

    // 시작하려면
    menubar->command();
}
/*
    * composite 패턴
        * 객체들을 트리 구조로 구성하여 부분과 전체를 나타내는 계층 구조로 만들 수 있다.
        * 개별 객체(Leaf)와 복합 객체(composite, node)를 구별 하지 않고 동일한 방법으로 다룰 수 있다.
        * 하위 메뉴를 얻는 getSubMenu() 추가
            *  getSubMenu() 를 파생 클래스에만 넣을 것인가? 기반 클래스에도 넣을 것인가?
            * 
    @startuml
        title Composite Pattern
        class Component{
            +operation()
            +add()
            +remove()
            +getchild()
        }
        class Leaf {
            +operation()
        }
        class Composite{
            +operation()
            +add()
            +remove()
            +getchild()
        }
        Component <|-down- Leaf
        Component <|-down- Composite
    @enduml
*/
#endif