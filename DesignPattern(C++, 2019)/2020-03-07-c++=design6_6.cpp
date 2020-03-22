#include <iostream>
#include <string>
using namespace std;

#define TEST (3)
// Factory Method
#if TEST == 1
// 입학 지원서
using Application = string; // class Application {}


// 지원서 만드는 클래스
class Director
{
    string name = "HONG";
    string phone = "010-111-1111";
    string address = "SEOUL KANGNAMGU";
public:
    Application construct()
    {
        Application app;
        app += name + "\n";
        app += phone + "\n";
        app += address + "\n";
        return app;
    }
};

int main()
{
    Director d;
    // 전화, 이름 입력...
    Application app = d.construct();
    cout << app << endl;
}
#elif TEST == 2
// 입학 지원서
/*
    * 지원서 객체는 다양한 형태로 생성 될 수 있어야 한다.
        * 지원서에는 이름, 전화번호, 주소의 순소로 표기 되어야한다.
        * 지원서는 상황에 따란 Raw Text, HTML , XML 방식으로 만들 수 있어야 한다.
    * 지원서를 만드는 공정은 변하지 않지만, 각 공정의 표현은 변해야한다.
        * 변하는 것은 분리 되어야 한다.
        * 
    * 변하는 것을 분리하는 방법 2가지
        * 변하는 것을 가상함수로 -> TEST 3
        * 변하는 것을 다른 클래스로  
*/
using Application = string; // class Application {}


// 지원서 만드는 클래스
class Director
{
    string name = "HONG";
    string phone = "010-111-1111";
    string address = "SEOUL KANGNAMGU";
public:
    Application construct()
    {
        Application app;
        app += name + "\n";
        app += phone + "\n";
        //app += address + "\n";
        return app;
    }
    Application XMLconstruct()
    {
        Application app;
        app += "<NAME>" + name + "</NAME>\n";
        app += phone + "\n";
        //app += address + "\n";
        return app;
    }
};

int main()
{
    Director d;
    // 전화, 이름 입력...
    Application app = d.construct();
    cout << app << endl;
}
#elif TEST == 3
/*
    * 빌더 패턴 의도
        * 복잡한 객체르 생성하는 방법과 표현하는 방법을 정의하는 클래스를 별도로 분리하여 
        * 서로 다른 표현이라도 이를 생성 할 수 있는 동일한 구축 공정을 제공 
    * 전략 패턴과의 차이 -> 알고리즘을 바꾸는 것
    * 빌더 패턴 -> 클래스를 만들 때
    * 상태패턴 -> 동작을 바꿀 때
 */
// 입학 지원서
using Application = string; // class Application {}


// 지원서의 각 단계의 표현을 만드는 빌더 인터페이스
struct IBuilder
{
    virtual ~IBuilder() {}
    virtual void makeName(string name) =  0;
    virtual void makePhone(string phone) =  0;
    virtual void makeAddress(string addr) =  0;

    virtual Application getResult() = 0;
};

// 지원서 만드는 클래스
class Director
{
    string name = "HONG";
    string phone = "010-111-1111";
    string address = "SEOUL KANGNAMGU";
    IBuilder* pBuilder;
public:
    void setBuilder( IBuilder* p ) { pBuilder = p;}

    Application construct()
    {
        pBuilder->makeName(name);
        pBuilder->makePhone(phone);
    //    pBuilder->makeAddress(address);

        return pBuilder->getResult();
    }
};

class XMLBuilder : public IBuilder
{
    Application app;
public:
    virtual void makeName(string name)
    {
        app += "<NAME>" + name + "</NAME>\n";
    }
    virtual void makePhone(string phone)
    {
        app += "<PHONE>" + phone + "</PHONE>\n";
    }
    virtual void makeAddress(string addr)
    {
        app += "<ADDRESS>" + addr + "</ADDRESS>\n";
    }

    virtual Application getResult() { return app;}
};

class TextBuilder : public IBuilder
{
    Application app;
public:
    virtual void makeName(string name)
    {
        app += name + "\n";
    }
    virtual void makePhone(string phone)
    {
        app += phone + "\n";
    }
    virtual void makeAddress(string addr)
    {
        app +=  addr + "\n";
    }

    virtual Application getResult() { return app;}
};

int main()
{
    Director d;
    XMLBuilder xb;
    d.setBuilder(&xb);

    Application app = d.construct();
    cout << app << endl;

    TextBuilder tb;
    d.setBuilder(&tb);
    app = d.construct();
    cout << app << endl;
}

#endif
// 핵심정리
/*
    * 생성 패턴 정리
        * GoF's 의 디자인 패턴의 분류
            * 생성패턴 - 5가지
            * 구조 패턴 7가지
            * 행위 패턴 - 11가지
        * **Singleton** - 클래스 인스턴스는 오직 하나임을 보장하며 이에 대한 접근은 어디에서든지 하나만 통일하여 제공
        * **Absctract Factory** - 상세화 된 서브 클래스를 정의하지 않고도 서로 관련성이 있거나 독립적인 여러객체의 군을 생성하기 위한 인터페이스를 제공
        * **Prototype** - 견본적 인스턴스 사용하여 생성할 객제의 종류를 명시하고 이렇게 만들어진 견본을 복사하여 새로운 객체를 생성한다.
        * **Builder** - 복잡한 객체를 생헌하는 방법과 표현하는 방법을 정의하는 클래스를 별로로 분리하여 서로 다른 표현이라도 이를 생성할 수 있는 동일한 구축 공정르 제공할수 있도록 한다.
        * **Factory Method** - 객체를 생성하기 위해 인터페이스를 정의 하지만, 어떤 클래스의 인스턴스를 생성할 지에 대한 결정은 서브 클래스가 한다. 클래스의 인스턴스를 만드는 시점을 서브클래스로 미룬다.
    * 구조 패턴의 종류
        * 문제를 해결하기 위해 간접층을 만드는 패턴
            * Adpater, Proxy, Bridege, Facade
        * 재귀적 포함을 사용하는 디지인패턴
            * Composite, Decorator
        * Flyweight
    * 행위 패턴
        *  **tempalte method, strategy state, iterator, visitor, observer** command, memeto, iterpret, mediator, chain of reponsibility
*/