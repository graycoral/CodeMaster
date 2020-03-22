
#include "menu.hpp"

using namespace std;

#define TEST (2)
// 메뉴의 이벤트 처리
#if TEST == 1

/*
    * 메뉴를 선택 할 때 하는 일은 메뉴 객체에 따라 다르다.
        * 메뉴 선택 시 하는일을 가상 함수로 분리하는 경우
*/

class MenuItem : public BaseMenu
{
    int id;
public:
    // MenuItem(int n) : id(n) {} - c++ 기본 문법 참조 
    MenuItem(string s, int n) : BaseMenu(s), id(n) {}
    virtual void command()
    {
        // 변해야하는 것을 가상함수로
        doCommand();
    }
    virtual void doCommand() {}
};

class AddStudent :public MenuItem
{
public:
    using MenuItem::MenuItem; // **생성자 상속**
    virtual void doCommand()
    {
        cout << "Addstudne" << endl;
    }
};

class RemoveStudent :public MenuItem
{
public:
    using MenuItem::MenuItem; // **생성자 상속**
    virtual void doCommand()
    {
        cout << "Removestudne" << endl;
    }
};

int main()
{    
    // MenuItem* m1 = new MenuItem("Add student", 11);
    // MenuItem* m2 = new MenuItem("Remove Student", 12);
    
    AddStudent m1("Add student", 11);
    RemoveStudent m2("Remove Student", 12);    
    
    m1.command();
    m2.command();
}
#elif TEST == 2

/*
    * 메뉴를 선택 할 때 하는 일은 메뉴 객체에 따라 다르다.
        * 변하는 것을 다른 클래스로
        * JAVA, c#, 안드로이드 앱등에서 사용되는 개념
        * **"Listner"** 라는 이름을 사용하는 기술
*/
// 메뉴 메시지를 처리하려면 아래 인터페이스를 정의 해야한다.
struct IMunuListner
{
    virtual void doCommand(int id) = 0;
    virtual ~IMunuListner() {}
};

class MenuItem : public BaseMenu
{
    int id;
    IMunuListner* pListner = 0;
public:
    void setLister(IMunuListner* p) {pListner = p;}
    MenuItem(string s, int n) : BaseMenu(s), id(n) {}
    virtual void command()
    {
        if(pListner != 0){
            pListner->doCommand();
        }   
    }    
};

class Dialog : public IMunuListner
{
public:
    virtual void doCommand(int idx)
    {
        cout << "doCommand()" << endl;
        switch(idx)
        {
        case 11: cout << "11" << endl; break;
        case 12: cout << "12" << endl; break;
        }
    }
};

int main()
{    
    Dialog dlg;
    MenuItem m1("Add student", 11);
    MenuItem m2("Remove Student", 12);

    m1.setLister(&dlg);
    m2.setLister(&dlg);

    m1.command();
    m2.command();
}
#elif TEST == 3
#endif