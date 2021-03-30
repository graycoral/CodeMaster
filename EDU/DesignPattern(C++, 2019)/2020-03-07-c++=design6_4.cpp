#include <iostream>
#include <vector>
#include <map>
#include "Singleton.h"
using namespace std;

#define TEST (2)
// Abstract Factory
#if TEST == 1
/*
    * QT 라이브러리의 특징
        * 프로그램 실행시 -style 옵션에 따라 GUI 모양이 달라진다.
        * test.exe -style=GTk
        * test.exe -style=Windows 
*/
struct IButton
{
    virtual void Draw() = 0;
    virtual ~IButton() {}
};

struct IEdit
{
    virtual void Draw() = 0;
    virtual ~IEdit() {}
};

struct WinButton : public IButton { void Draw() {cout << "Draw Win Button" << endl;}}
struct GTKButton : public IButton { void Draw() {cout << "Draw GTK Button" << endl;}}

struct WinEdit : public IEdit { void Draw() {cout << "Draw Win Button" << endl;}}
struct GTKEdit : public IEdit { void Draw() {cout << "Draw GTK Button" << endl;}}

int main(int argv, char** argc)
{
    IButton* pBtn;
    if(strcmp(argc[1], "Windows") == 0)
        pBtn = new WinButton;
    else
        pBtn = new GTKButton;
    
    pBtn->Draw();
}

#elif TEST == 2
/*
    * Abstrct Pattern
        * 여러 객체의 군을 생성하기 위한 인터페이스를 제공한다.
    @startuml
        class AbstractProduct <<interface>> 
        {
        }
        class ConcreteProduct {
        }

        class AbstractFactory <<interface>> 
        {
        +CreateProductA() : virtual
        +CreateProductB() : virtual
        }

        class ConcreteFactory {
        +CreateProductA() : virtual
        +CreateProductB() : virtual
        }

        class Client

        Client -up-* AbstractProduct
        Client -up-* AbstractFactory

        AbstractProduct <|-down- ConcreteProduct
        AbstractFactory <|-down- ConcreteFactory
    @enduml
*/
struct IButton
{
    virtual void Draw() = 0;
    virtual ~IButton() {}
};

struct IEdit
{
    virtual void Draw() = 0;
    virtual ~IEdit() {}
};
//-----------------------------
// Factory의 공통의 기반 클래스

struct IFactory
{
    virtual IButton* CreateButton() = 0;
    virtual IEdit* CreateEdit() = 0;
    virtual ~IFactory() {}
};

struct WinButton : public IButton { void Draw() {cout << "Draw Win Button" << endl;}}
struct GTKButton : public IButton { void Draw() {cout << "Draw GTK Button" << endl;}}

struct WinEdit : public IEdit { void Draw() {cout << "Draw Win Button" << endl;}}
struct GTKEdit : public IEdit { void Draw() {cout << "Draw GTK Button" << endl;}}

struct WinFactory : public IFactory
{
    IButton* CreateButton() {return new WinButton;}
    IEdit* CreateEdit() {return new WinEdit;} 
};

struct GTKFactory : public IFactory
{
    IButton* CreateButton() {return new GTKButton;}
    IEdit* CreateEdit() {return new GTKEdit;} 
};


int main(int argv, char** argc)
{
    // IButton* pBtn;
    IFactory* pFactory;
    if(strcmp(argc[1], "Windows") == 0)
        pFactory = new WinButton;
    else
        pFactory = new GTKButton;
    pFactory->Draw();

    IButton* pBtn = pFactory->CreateButton(); 
}
























//

#endif