#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define TEST (5)

#if TEST == 1
// Decorator #1
/*
    * Decorator 패턴
        *  **실행 시간에 객체에 기능을 추가** 할때 사용하는 패턴
        * 우주선이 아이템 획득시 기존 미사일에 새로운 미사일이 추가되는 경우
*/
class SpaceCraft
{
    int color;
    int speed;
public:
    void Fire() { cout << "Space Craft :  ------------" << endl;}
};

int main()
{
    SpaceCraft sc;
    sc.Fire();
}

#elif TEST == 2
// Decorator #1
/*
    * 상속을 통한 기능의 추가
        * 객체가 아닌 클래스에 기능을 추가
        * 실행시간이 아닌 코드 작성시에 기능이 추가
*/
class SpaceCraft
{
    int color;
    int speed;
public:
    void Fire() { cout << "Space Craft :  ------------" << endl;}
};

class LeftMissile : public SpaceCraft
{
    void Fire()
    {
        SpaceCraft::Fire(); // 기존 기능 수행
        cout << "Lef tMissile :  >>>>>>>>>>>>>>>>" << endl;
    }
};

int main()
{
    SpaceCraft sc;
    sc.Fire();

    LeftMissile lm; // 새로운 객체를 만듬. sc와 전혀 관계가 없음
    lm.Fire();
}
#elif TEST == 3
// Decorator #1
/*
    * 구성(composition)을 통한 기능의 추가 -> 유연성이 뛰어나고 동적으로 동작한다.
        * 클래스가 아닌 **객체에 기능 추가**
        * 컴파일 시간이 아닌 **실행 시간에 기능 추가**
*/
class SpaceCraft
{
    int color;
    int speed;
public:
    void Fire() { cout << "Space Craft :  ------------" << endl;}
};

//구성(composition)을 통한 기능의 추가
class LeftMissile
{
    SpaceCraft* craft;
public:
    LeftMissile(SpaceCraft* p) : craft(p) {}
    void Fire()
    {
        craft->Fire(); // 기존 기능 수행
        cout << "Lef tMissile :  >>>>>>>>>>>>>>>>" << endl;
    }
};

int main()
{
    SpaceCraft sc;
    sc.Fire();

    LeftMissile lm(&sc);
    lm.Fire();
}
#elif TEST == 4
// Decorator #2
/*
    @startuml
    class Component
    class SpaceCraft
    class LeftMissile {
    +Component* craft
    }
    class RightMissle {
    +Component* craft
    }
    Component <|-down- SpaceCraft
    Component <|-down- LeftMissile
    Component <|-down- RightMissle
    @enduml

    * 우주선과 기능 추가 객체는 동일한 기반 클래스를 가져야 한다.
*/
struct Componet
{
    virtual void Fire() = 0;
    virtual ~Componet() {}
};
class SpaceCraft : public Componet
{
    int color;
    int speed;
public:
    void Fire() { cout << "Space Craft :  ------------" << endl;}
};

//구성(composition)을 통한 기능의 추가
class LeftMissile : public Componet
{
    Componet* craft;
public:
    LeftMissile(Componet* p) : craft(p) {}
    void Fire()
    {
        craft->Fire(); // 기존 기능 수행
        cout << "Lef tMissile :  >>>>>>>>>>>>>>>>" << endl;
    }
};
class RightMissile : public Componet
{
    Componet* craft;
public:
    RightMissile(Componet* p) : craft(p) {}
    void Fire()
    {
        craft->Fire(); // 기존 기능 수행
        cout << "Right tMissile :  >>>>>>>>>>>>>>>>" << endl;
    }
};

int main()
{
    SpaceCraft sc;
    sc.Fire();

    LeftMissile lm(&sc);
    lm.Fire();

    // RightMissile rm(&sc);
    RightMissile rm(&lm); // 기능 추가된 객체에 다시 기능 추가
    rm.Fire();
}
#elif TEST == 5
// Decorator #2
/*
    @startuml
    class Component
    class SpaceCraft
    class IDecorator {
        +Component* craft    
    }
    class LeftMissile 
    class RightMissle
    Component <|-down- SpaceCraft
    Component <|-down- IDecorator    
    IDecorator <|-down- LeftMissile
    IDecorator <|-down- RightMissle
    @enduml

    * 우주선과 기능 추가 객체는 동일한 기반 클래스를 가져야 한다.    *  
    * Component : concrete Component
    * LeftMissile, RightMissle : Concrete Decorator
    * Decorator 패턴의 의도
        * 객체에 동적으로 새로운 서비스를 추가 할 수 있다.
        * 기능 추가를 위해 서브 클래스를 사용하는 것 보다 융통성 있는 방법을 제공한다.
*/
struct Componet
{
    virtual void Fire() = 0;
    virtual ~Componet() {}
};
class SpaceCraft : public Componet
{
    int color;
    int speed;
public:
    void Fire() { cout << "Space Craft :  ------------" << endl;}
};

//구성(composition)을 통한 기능의 추가

//---
// 기능 추가 클래스의 공통의 기반 클래스
class IDecorator : public Componet{
    Componet* craft;
public:
    IDecorator(Componet* p) : craft(p) {}
    void Fire() { craft->Fire();}
};

class LeftMissile : public IDecorator
{    
public:
    LeftMissile(Componet* p) : IDecorator(p) {}
    void Fire()
    {
        IDecorator::Fire();
        cout << "Lef tMissile :  >>>>>>>>>>>>>>>>" << endl;
    }
};
class RightMissile : public IDecorator
{    
public:
    RightMissile(Componet* p) : IDecorator(p) {}
    void Fire()
    {
        IDecorator::Fire();
        cout << "Right tMissile :  >>>>>>>>>>>>>>>>" << endl;
    }
};

int main()
{
    SpaceCraft sc;
    sc.Fire();

    LeftMissile lm(&sc);
    lm.Fire();

    // RightMissile rm(&sc);
    RightMissile rm(&lm); // 기능 추가된 객체에 다시 기능 추가
    rm.Fire();
}
#elif TEST == 6
#elif TEST == 7
#endif