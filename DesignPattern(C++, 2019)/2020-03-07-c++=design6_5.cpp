#include <iostream>
#include <vector>
#include <map>
#include "Singleton.h"
using namespace std;

#define TEST (2)
// Factory Method
#if TEST == 1

struct IEdit
{
    virtual void Draw() = 0;
    virtual ~IEdit() {}
};
struct IButton
{
    virtual void Draw() = 0;
    virtual ~IButton() {}
};

struct WinButton : public IButton { void Draw() { cout << "Draw WinButton" << endl;}};
struct GTKButton : public IButton { void Draw() { cout << "Draw GTKButton" << endl;}};

struct WinEdit : public IEdit { void Draw() { cout << "Draw WinEdit" << endl;}};
struct GTKEdit : public IEdit { void Draw() { cout << "Draw GTKEdit" << endl;}};

//---------------------------------------------------
// -style 옵션에 상관없이 무조건 windows 스타일 사용
class WinDialog
{
public:
    void Init()
    {
        WinButton* pBtn = new WinButton;
        WinEdit*   pEdit = new WinEdit;

        //pBtn->Move();
        //pEdit->Move();

        pBtn->Draw();
        pEdit->Draw();
    }
};

class GTKDialog
{
public:
    void Init()
    {
        GTKButton* pBtn = new GTKButton;
        GTKEdit*   pEdit = new GTKEdit;

        //pBtn->Move();
        //pEdit->Move();

        pBtn->Draw();
        pEdit->Draw();
    }
};
int main()
{
    WinDialog dlg;
    dlg.Init();
}
#elif TEST == 2
/*
    * factory method 의도
        * 객체를 생서하기 위해 인터페이스를 정의 하지만, 어떤 클래스의 인터스턴스를 생성할지에 대한 결정은 서브 클래스가 한다.
        * factory method 패턴에서는 클래스의 인스턴스를 만드는 시점을 서브 클래스로 미룬다.
        * template method와 유사한 형태이다.
*/ 
struct IEdit
{
    virtual void Draw() = 0;
    virtual ~IEdit() {}
};
struct IButton
{
    virtual void Draw() = 0;
    virtual ~IButton() {}
};

struct WinButton : public IButton { void Draw() { cout << "Draw WinButton" << endl;}};
struct GTKButton : public IButton { void Draw() { cout << "Draw GTKButton" << endl;}};

struct WinEdit : public IEdit { void Draw() { cout << "Draw WinEdit" << endl;}};
struct GTKEdit : public IEdit { void Draw() { cout << "Draw GTKEdit" << endl;}};

//---------------------------------------------------

class BaseDialog
{
public:
    void Init()
    {
        IButton* pBtn = CreateButton();
        IEdit*   pEdit = CreateEdit();

        //pBtn->Move();
        //pEdit->Move();

        pBtn->Draw();
        pEdit->Draw();
    }
    virtual IButton* CreateButton() = 0; // 전체의 흐림이 같을 때 가상 함수를 이용한다. // template 메소드라 불러도 무관
    virtual IEdit*   CreateEdit() = 0;
};


class WinDialog : public BaseDialog
{
public:
    virtual IButton* CreateButton() { return new WinButton;}
    virtual IEdit* CreateEdit()    { return new WinEdit;}
};

class GTKDialog : public BaseDialog
{
public:
    virtual IButton* CreateButton() { return new GTKButton;}
    virtual IEdit* CreateEdit()   { return new GTKEdit;}
};

int main()
{
    WinDialog dlg;
    dlg.Init();
}


#endif