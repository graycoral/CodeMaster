
#include "menu.hpp"

using namespace std;

#define TEST (4)
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

    m1.setLister(&dlg); // 함수에 대한 정보는 없고 메뉴만 선택한다(함수에 대한 정보는 Interface에 있다.)
    m2.setLister(&dlg);

    m1.command();
    m2.command();
}
#elif TEST == 3
// 메뉴에 객체가 아닌 함수를 연결한다.
// 범용적인 함수 포인터를 만들어보자

class MenuItem : public BaseMenu
{
    int id;

    void (Dialog::*handler)();
    Dialog* target;
public:
    void setHandler(void(*f)()) {handler = f;}
    MenuItem(string s, int n) : BaseMenu(s), id(n) {}
    virtual void command()
    {
        if(pListner != 0){
            pListner->doCommand();
        }
    }
};

struct IAction
{
    virtual void Excute() = 0;
    virtual ~IAction() {}
};

class FuctionAction :public IAction
{
    typedef void(*FP)();
    FP handler;
};

template<typename T>
class MemberAction :public IAction
{
    typedef void(T::*FP)();

    FP handler;
    T* target;
public:
    MemberAction(FP f, T* obj): handler(f), target(obj) {}
    virtual void Excute() {target->*handler();}
};

void foo() { cout << "foo" << endl;}

class Dialog
{
public:
    void Close() {cout << "Dialog Close" << endl;}
};


int main()
{
    // void(*f1)() = &foo;
    IAction* p = new FuctionAction(&foo);
    // void(Dialog::*f2)() = &Dialog::Close;
    IAction* p2 = new MemberAction<Dialog>(&Dialog::Close, &dlg); // 어려워 보이고 불펺다ㅏ.

    p->Excute(); // foo 실행
    p2->Excute(); // Diaglog::Close
}
#elif TEST == 4
/*
    * 함수템플릿 vs 클래스 템플릿
        * 함수 템플릿은 타입을 명시적으로 지정하지 않아도 컴파일러가 함수 인자를 통해서 타입을 추론 할 수 있다.
        * 클래스 템플릿은 타입을 반드시 명시적으로 전달해야한다.
        * **클래스 템플릿을 생성하는 함수 템플릿을 도움 함수를 만들면 편하다.**
 */
struct IAction
{
    virtual void Excute() = 0;
    virtual ~IAction() {}
};

class FuctionAction :public IAction
{
    typedef void(*FP)();
    FP handler;
};

template<typename T>
class MemberAction :public IAction
{
    typedef void(T::*FP)();

    FP handler;
    T* target;
public:
    MemberAction(FP f, T* obj): handler(f), target(obj) {}
    virtual void Excute() {target->*handler();}
};

void foo() { cout << "foo" << endl;}

class Dialog
{
public:
    void Close() {cout << "Dialog Close" << endl;}
};

//함수 템플릿
template<typename T>
MemberAction<T>* action(void(T::*f)()., T* obj)
{
    return new MemberAction<T>(f, obj);
}

template<typename T>
FunctionAction<T>* action(void(*f)())
{
    return new FunctionAction<T>(f);
}

int main()
{
    Dialog dlg;
    // IAction* p = new FuctionAction(&foo);
    IAction* p = action(&foo);
    // IAction* p2 = new MemberAction<Dialog>(&Dialog::Close, &dlg);
    IAction* p2 = action(&Dialog::Close, &dlg);

    p->Excute(); // foo 실행
    p2->Excute(); // Diaglog::Close
}
#endif