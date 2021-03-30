#include <iostream>
#include <vector>
#include <list>

using namespace std;
#define TEST    (4)
// Vistor
/*
    * Vistor pattern의 의도
        * 객제구조에 속한 요소에 수행할 오퍼레이션을 정의하는 객체 
        * **클래스를 변경하지 않고(멤버 함수를 추가하지 않고) 새로운 오퍼레이션을 정의 할 수 있게 한다.
*/
#if TEST == 1
int main()
{
    list<int> s= {1,2,3,4,5,6,7,8,9,10};
    // 모든 요소를 2배로 만들고 싶다.
    // 방법 1. 외부에서 직접 연산 수행
    for(auto&n : s){
        // TBD 
    }
    // 방법 2. 멤버 함수로 기능을 제공
    s.twice_all_element();
    s.show_all_element();

    // 방법 3. 방문자 패턴을 사용한다.
    TwiceVistor<int> tv;// 방문자
    s.accept(&tv);

    ShowVisitor<int> sv; // 방문자
    s.accept(&tv);

} 
#elif TEST == 2
// visitor 구현
/*
    * 복합 객체의 accept 함수는 다양한 방분자를 받을 수 있어야한다,.
        * 모든 방문자의 인터페이스가 필요하다 - IVisitor
        * **클래스를 변경하지 않고(멤버함수를 추가하지 않고) 새로운 오퍼레이션을 정의 할 수있게 한다.**
    * 모든 방문 대상 객체(복합체)는 accpet가 있어야 한다.
        * IAccept 인터페이스 
*/

// 방문자(visitor)의 인터페이스
template<typename T> struct IVisitor
{
    virtual void visit(T& elem) =0;
    virtual ~IVisitor() {}
};

template<typename T> class TwiceVisitor : public IVisitor<T>
{
public:
    virtual void visit(T& elem) { elem = elem *2;}
};

template<typename T> class ShowVisitor : public IVisitor<T>
{
public:
    virtual void visit(T& elem) { cout << elem << endl;}
};

//방문의 대상의 인터페이스
template<typename T> struct IAcceptor
{
    virtual void accept(IVisitor<T>* p) = 0;
    virtual ~IAcceptor() {}
};

template<typename T> class List : public list<T>, public IAcceptor<T>
{
public: 
    using list<T>::list;
    virtual void accept(IVisitor<T>* p)
    {
        // 모든 요소를 방문자에게 전달.
        for(auto& e: *this){
            p->visit(e);
        }
    }
};


int main()
{
    List<int> s= {1,2,3,4,5,6,7,8,9,10};
  
    TwiceVisitor<int> tv;// 방문자
    s.accept(&tv);

    ShowVisitor<int> sv; // 방문자
    s.accept(&tv);
} 
#elif TEST == 3
// 메뉴 예제와 방문자
/*
    * 메뉴 예제와 방문자
        * 메뉴 중에 팝업메뉴의 title을 강조하고 싶다.
        * 전통적인 객체지향 디자인에서 새로운 가상함수를 추가하는 것은 쉽지 않다,.
        * 방문자 패턴은 클래스를 변경하지 않고 오퍼레이션을 추가 할 수 있다.
     
    * 방문자 패턴의 특징
        * 캡술화/정보 은익을 위반 하개 된다. 
*/
//
//---------------------------
class BaseMenu;
class MenuItem;
class PopupMenu;

// 방문자의 인터페이스
struct IMenuVisitor
{
    virtual ~IMenuVisitor() {}

    virtual void visit(BaseMenu* p) = 0;
    virtual void visit(MenuItem* p) = 0;
    virtual void visit(PopupMenu* p) = 0;
    // virtual void visit(PopupMenu* p) = 0;
};

struct IAcceptor
{
    virtual ~IAcceptor() {}
    virtual void accept(IMenuVisitor* p) = 0;
};
//-----------------------------------------------

class BaseMenu : public IAcceptor
{
    string title;
public:
    BaseMenu( string s) : title(s) {}
    void setTitle(string s) { title = s;}
    string getTitle() const { return title;}

    virtual void command() = 0;
};

class MenuItem : public BaseMenu
{
    int id;
public:
    virtual void accept(IMenuVisitor* p)
    {
        p->visit(this);
    }

    MenuItem(string s, int n) : BaseMenu(s),  id(n) {}

    virtual void command()
    {
        cout << getTitle() << endl;
        getchar();
    }
};


class PopupMenu : public BaseMenu
{
    vector<BaseMenu*> v;
public:
    PopupMenu( string s) : BaseMenu(s) {}




    void addMenu(BaseMenu* p) { v.push_back(p);}

    virtual void command()
    {
        while( 1 )
        {
            system("cls");

            int sz = v.size();

            for ( int i = 0; i < sz; i++)
            {
                cout << i + 1 << ". " << v[i]->getTitle() << endl;
            }

            cout << sz + 1 << ". << back " << endl;

            //------------------------------
            int cmd;
            cout << "choose menu >> ";
            cin >> cmd;

            if ( cmd < 1 || cmd > sz + 1 ) // 잘못된 입력
                continue;

            if ( cmd == sz + 1 )
                break;


            // 선택된 메뉴 실행..
            v[cmd-1]-> command(); // 핵심.. !
        }

    }
    virtual void accept(IMenuVisitor* p)
    {
        p->visit(this);

        for ( auto m : v)
            m->accept(p);
    }
};

class MenuTitleChangeVisitor : public IMenuVisitor
{
public:
    virtual void visit(BaseMenu* p) {}
    virtual void visit(MenuItem* p) {}
    virtual void visit(PopupMenu* p)
    {
        // popupmenu 의 타이틀을 변경한다.
        string s = p->getTitle();
        s = "[ " + s + " ]";

        p->setTitle(s);
    }
};

class EraseTitleChangeVisitor : public IMenuVisitor
{
public:
    virtual void visit(BaseMenu* p) {}
    virtual void visit(MenuItem* p) {}
    virtual void visit(PopupMenu* p)
    {
        p->setTitle("...");
    }
};

int main()
{
    PopupMenu* p1 = new PopupMenu("MENUBAR");

    p1->addMenu( new PopupMenu("SCREEN"));
    p1->addMenu( new PopupMenu("SOUND"));
    p1->addMenu( new MenuItem("power off", 11));

    // [SCREEN]
    // p1 은복합객체
    // 방법1. 타이틀을 변경하는 멤버 함수
    // 방법2. 방문자 패턴
    //---------------------
    MenuTitleChangeVisitor mtcv;
    p1->accept(&mtcv);

    EraseTitleChangeVisitor etcv;
    p1->accept(&etcv);
    // 1. 메뉴 (복합객체)는 accept 가 필요
    // 2. 방문자 인터페이스 필요..

    p1->command();
}
#elif TEST == 4
/*
    * 방문자 패턴의 특징
    * 새로운 클래스 추가(쉽다) vs 가상함수 추가(모든 파생클래스가 변경된다.)
    * 일반적인 객체지향 프로그래밍에서는 새로운 타입을 추가하기는 쉽지만 새로운 함수를 추가하기는 어렵다.
    * 방문재 패턴은 새로운 오퍼레이션을 추가하기는 쉽지만 타입을 추가하기는 어렵게 된다. 
*/
#endif